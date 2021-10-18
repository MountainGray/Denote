#include "offscreenopengl.h"

#include <QtGui/QOpenGLContext>
#include <QtGui/QOffscreenSurface>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/qpa/qplatformwindow.h>
#include <QtGui/qpa/qplatformintegration.h>
#include <QtOpenGL/QOpenGLFramebufferObject>
#include <QtOpenGL/QOpenGLPaintDevice>

#include <QtGui/private/qguiapplication_p.h>
#include <QtOpenGL/private/qopenglframebufferobject_p.h>
#include <QtOpenGL/private/qopenglpaintdevice_p.h>
#include <QtOpenGL/qpa/qplatformbackingstoreopenglsupport.h>

QT_BEGIN_NAMESPACE

class OffscreenOpenGLPaintDevicePrivate : public QOpenGLPaintDevicePrivate
{
public:
    explicit OffscreenOpenGLPaintDevicePrivate(OffscreenOpenGL *offscreen)
        : QOpenGLPaintDevicePrivate(QSize()),
          ogl(offscreen) { }
    void endPaint() override;
    OffscreenOpenGL *ogl;
};

class OffscreenOpenGLPaintDevice : public QOpenGLPaintDevice
{
public:
    explicit OffscreenOpenGLPaintDevice(OffscreenOpenGL *offscreen)
        : QOpenGLPaintDevice(*new OffscreenOpenGLPaintDevicePrivate(offscreen)) { }
    void ensureActiveTarget() override;
};

class OffscreenOpenGLPrivate : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(OffscreenOpenGL)

public:
    OffscreenOpenGLPrivate(QWidget* widget = nullptr) : subject(widget) { }

    void reset();
    void recreateFbo();

    GLuint textureId() const;

    void initialize();
    void invokeUserPaint();
    void render();

    void invalidateFbo();

    QImage grabFramebuffer();
    void beginBackingStorePainting() { inBackingStorePaint = true; }
    void endBackingStorePainting() { inBackingStorePaint = false; }
    void beginCompose();
    void endCompose();
    void initializeViewportFramebuffer();
    void resizeViewportFramebuffer();
    void resolveSamples();

    QWidget *subject = nullptr;
    QOpenGLContext *context = nullptr;
    QOpenGLFramebufferObject *fbo = nullptr;
    QOpenGLFramebufferObject *resolvedFbo = nullptr;
    QOffscreenSurface *surface = nullptr;
    OffscreenOpenGLPaintDevice *paintDevice = nullptr;
    int requestedSamples = 0;
    GLenum textureFormat = 0;
    QSurfaceFormat requestedFormat = QSurfaceFormat::defaultFormat();
    OffscreenOpenGL::UpdateBehavior updateBehavior = OffscreenOpenGL::PartialUpdate;
    bool initialized = false;
    bool fakeHidden = false;
    bool inBackingStorePaint = false;
    bool hasBeenComposed = false;
    bool flushPending = false;
};

void OffscreenOpenGLPaintDevicePrivate::endPaint()
{
    OffscreenOpenGLPrivate *ogld = static_cast<OffscreenOpenGLPrivate *>(QObjectPrivate::get(ogl));
    if (!ogld->initialized)
        return;

    QOpenGLContextPrivate::get(ogld->context)->defaultFboRedirect = 0;
}

void OffscreenOpenGLPaintDevice::ensureActiveTarget()
{
    OffscreenOpenGLPaintDevicePrivate *d = static_cast<OffscreenOpenGLPaintDevicePrivate *>(d_ptr.data());
    OffscreenOpenGLPrivate *ogld = static_cast<OffscreenOpenGLPrivate *>(QObjectPrivate::get(d->ogl));
    if (!ogld->initialized)
        return;
    if (QOpenGLContext::currentContext() != ogld->context)
        d->ogl->makeCurrent();
    else
        ogld->fbo->bind();
    QOpenGLContextPrivate::get(ogld->context)->defaultFboRedirect = ogld->fbo->handle();
    // When used as a viewport, drawing is done via opening a QPainter on the widget
    // without going through paintEvent(). We will have to make sure a glFlush() is done
    // before the texture is accessed also in this case.
    ogld->flushPending = true;
}

GLuint OffscreenOpenGLPrivate::textureId() const
{
    return resolvedFbo ? resolvedFbo->texture() : (fbo ? fbo->texture() : 0);
}

void OffscreenOpenGLPrivate::reset()
{
    Q_Q(OffscreenOpenGL);

    // Destroy the OpenGL resources first. These need the context to be current.
    if (initialized)
        q->makeCurrent();

    delete paintDevice;
    paintDevice = nullptr;

    delete fbo;
    fbo = nullptr;
    delete resolvedFbo;
    resolvedFbo = nullptr;
    if (initialized)
        q->doneCurrent();

    // Delete the context first, then the surface. Slots connected to
    // the context's aboutToBeDestroyed() may still call makeCurrent()
    // to perform some cleanup.
    delete context;
    context = nullptr;
    delete surface;
    surface = nullptr;
    initialized = fakeHidden = inBackingStorePaint = false;
}

void OffscreenOpenGLPrivate::recreateFbo()
{
    Q_Q(OffscreenOpenGL);

    emit q->aboutToResize();

    context->makeCurrent(surface);

    delete fbo;
    fbo = nullptr;
    delete resolvedFbo;
    resolvedFbo = nullptr;

    int samples = requestedSamples;
    QOpenGLExtensions *extfuncs = static_cast<QOpenGLExtensions *>(context->functions());
    if (!extfuncs->hasOpenGLExtension(QOpenGLExtensions::FramebufferMultisample))
        samples = 0;

    QOpenGLFramebufferObjectFormat format;
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    format.setSamples(samples);
    if (textureFormat)
        format.setInternalTextureFormat(textureFormat);

    const QSize deviceSize = subject->size() * subject->devicePixelRatio();
    fbo = new QOpenGLFramebufferObject(deviceSize, format);
    if (samples > 0)
        resolvedFbo = new QOpenGLFramebufferObject(deviceSize);

    textureFormat = fbo->format().internalTextureFormat();

    fbo->bind();
    context->functions()->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    flushPending = true; // Make sure the FBO is initialized before use

    paintDevice->setSize(deviceSize);
    paintDevice->setDevicePixelRatio(subject->devicePixelRatio());

    emit q->resized();
}

void OffscreenOpenGLPrivate::beginCompose()
{
    Q_Q(OffscreenOpenGL);
    if (flushPending) {
        flushPending = false;
        q->makeCurrent();
        static_cast<QOpenGLExtensions *>(context->functions())->flushShared();
    }
    hasBeenComposed = true;
    emit q->aboutToCompose();
}

void OffscreenOpenGLPrivate::endCompose()
{
    Q_Q(OffscreenOpenGL);
    emit q->frameSwapped();
}

void OffscreenOpenGLPrivate::initialize()
{
    Q_Q(OffscreenOpenGL);

    if (initialized || !subject)
        return;

    // Do not include the sample count. Requesting a multisampled context is not necessary
    // since we render into an FBO, never to an actual surface. What's more, attempting to
    // create a pbuffer with a multisampled config crashes certain implementations. Just
    // avoid the entire hassle, the result is the same.
    requestedSamples = requestedFormat.samples();
    requestedFormat.setSamples(0);

    context = new QOpenGLContext();
    context->setFormat(requestedFormat);

    if (Q_UNLIKELY(!context->create())) {
        qWarning("QOpenGLWidget: Failed to create context");
        return;
    }

    // The top-level window's surface is not good enough since it causes way too
    // much trouble with regards to the QSurfaceFormat for example. So just like
    // in QQuickWidget, use a dedicated QOffscreenSurface.
    surface = new QOffscreenSurface;
    surface->setFormat(context->format());
    surface->setScreen(context->screen());
    surface->create();

    if (Q_UNLIKELY(!context->makeCurrent(surface))) {
        qWarning("QOpenGLWidget: Failed to make context current");
        return;
    }

    paintDevice = new OffscreenOpenGLPaintDevice(q);
    paintDevice->setSize(subject->size() * subject->devicePixelRatio());
    paintDevice->setDevicePixelRatio(subject->devicePixelRatio());

    initialized = true;
}

void OffscreenOpenGLPrivate::resolveSamples()
{
    Q_Q(OffscreenOpenGL);
    if (resolvedFbo) {
        q->makeCurrent();
        QRect rect(QPoint(0, 0), fbo->size());
        QOpenGLFramebufferObject::blitFramebuffer(resolvedFbo, rect, fbo, rect);
        flushPending = true;
    }
}

void OffscreenOpenGLPrivate::invokeUserPaint()
{
    QOpenGLContext *ctx = QOpenGLContext::currentContext();
    Q_ASSERT(ctx && fbo);

    QOpenGLFunctions *f = ctx->functions();
    QOpenGLContextPrivate::get(ctx)->defaultFboRedirect = fbo->handle();

    f->glViewport(0, 0, subject->width() * subject->devicePixelRatio(), subject->height() * subject->devicePixelRatio());
    flushPending = true;

    QOpenGLContextPrivate::get(ctx)->defaultFboRedirect = 0;
}

void OffscreenOpenGLPrivate::render()
{
    Q_Q(OffscreenOpenGL);

    if (fakeHidden || !initialized)
        return;

    q->makeCurrent();

    if (updateBehavior == OffscreenOpenGL::NoPartialUpdate && hasBeenComposed) {
        invalidateFbo();
        hasBeenComposed = false;
    }

    invokeUserPaint();
}

void OffscreenOpenGLPrivate::invalidateFbo()
{
    QOpenGLExtensions *f = static_cast<QOpenGLExtensions *>(QOpenGLContext::currentContext()->functions());
    if (f->hasOpenGLExtension(QOpenGLExtensions::DiscardFramebuffer)) {
        const int gl_color_attachment0 = 0x8CE0;  // GL_COLOR_ATTACHMENT0
        const int gl_depth_attachment = 0x8D00;   // GL_DEPTH_ATTACHMENT
        const int gl_stencil_attachment = 0x8D20; // GL_STENCIL_ATTACHMENT
#ifdef Q_OS_WASM
        // webgl does not allow separate depth and stencil attachments
        // QTBUG-69913
        const int gl_depth_stencil_attachment = 0x821A; // GL_DEPTH_STENCIL_ATTACHMENT
        const GLenum attachments[] = {
            gl_color_attachment0, gl_depth_attachment, gl_stencil_attachment, gl_depth_stencil_attachment
        };
#else
        const GLenum attachments[] = {
            gl_color_attachment0, gl_depth_attachment, gl_stencil_attachment
        };
#endif
        f->glDiscardFramebufferEXT(GL_FRAMEBUFFER, sizeof attachments / sizeof *attachments, attachments);
    } else {
        f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }
}

QImage OffscreenOpenGLPrivate::grabFramebuffer()
{
    Q_Q(OffscreenOpenGL);

    initialize();
    if (!initialized)
        return QImage();

    if (!fbo) // could be completely offscreen, without ever getting a resize event
        recreateFbo();

    render();

    if (resolvedFbo) {
        resolveSamples();
        resolvedFbo->bind();
    } else {
        q->makeCurrent();
    }

    const bool hasAlpha = q->format().hasAlpha();
    QImage res = qt_gl_read_framebuffer(subject->size() * subject->devicePixelRatio(), hasAlpha, hasAlpha);
    res.setDevicePixelRatio(subject->devicePixelRatio());

    // While we give no guarantees of what is going to be left bound, prefer the
    // multisample fbo instead of the resolved one. Clients may continue to
    // render straight after calling this function.
    if (resolvedFbo)
        q->makeCurrent();

    return res;
}

void OffscreenOpenGLPrivate::initializeViewportFramebuffer()
{
    //Legacy behavior for compatibility with QGLWidget when used as a graphics view
    //viewport: enable clearing on each painter begin.
    subject->setAutoFillBackground(true);
}

void OffscreenOpenGLPrivate::resizeViewportFramebuffer()
{
    if (!initialized || !subject)
        return;

    if (!fbo || subject->size() * subject->devicePixelRatio() != fbo->size()) {
        recreateFbo();
    }
}

OffscreenOpenGL::OffscreenOpenGL(QWidget* subject)
    : QObject(*new OffscreenOpenGLPrivate(subject))
{
    if (Q_UNLIKELY(!QGuiApplicationPrivate::platformIntegration()->hasCapability(QPlatformIntegration::RasterGLSurface)))
        qWarning("QOpenGLWidget is not supported on this platform.");
}

/*!
  Destroys the QOpenGLWidget instance, freeing its resources.

  The QOpenGLWidget's context is made current in the destructor, allowing for
  safe destruction of any child object that may need to release OpenGL
  resources belonging to the context provided by this widget.

  \warning if you have objects wrapping OpenGL resources (such as
  QOpenGLBuffer, QOpenGLShaderProgram, etc.) as members of a OpenGLWidget
  subclass, you may need to add a call to makeCurrent() in that subclass'
  destructor as well. Due to the rules of C++ object destruction, those objects
  will be destroyed \e{before} calling this function (but after that the
  destructor of the subclass has run), therefore making the OpenGL context
  current in this function happens too late for their safe disposal.

  \sa makeCurrent
*/
OffscreenOpenGL::~OffscreenOpenGL()
{
    Q_D(OffscreenOpenGL);
    d->reset();
}

void OffscreenOpenGL::setSubject(QWidget *subject)
{
    Q_D(OffscreenOpenGL);
    d->subject = subject;
    d->initialize();
    if (!d->initialized)
        return;
    d->recreateFbo();
}

QWidget *OffscreenOpenGL::subject() const
{
    Q_D(const OffscreenOpenGL);
    return d->subject;
}

void OffscreenOpenGL::setPainter(QPainter *painter)
{
    Q_D(OffscreenOpenGL);
    painter->begin(d->paintDevice);
}

QPaintDevice *OffscreenOpenGL::paintDevice() const
{
    Q_D(const OffscreenOpenGL);
    return d->paintDevice;
}

/*!
  Sets this widget's update behavior to \a updateBehavior.
  \since 5.5
*/
void OffscreenOpenGL::setUpdateBehavior(UpdateBehavior updateBehavior)
{
    Q_D(OffscreenOpenGL);
    d->updateBehavior = updateBehavior;
}

/*!
  \return the update behavior of the widget.
  \since 5.5
*/
OffscreenOpenGL::UpdateBehavior OffscreenOpenGL::updateBehavior() const
{
    Q_D(const OffscreenOpenGL);
    return d->updateBehavior;
}

/*!
  Sets the requested surface \a format.

  When the format is not explicitly set via this function, the format returned by
  QSurfaceFormat::defaultFormat() will be used. This means that when having multiple
  OpenGL widgets, individual calls to this function can be replaced by one single call to
  QSurfaceFormat::setDefaultFormat() before creating the first widget.

  \note Requesting an alpha buffer via this function will not lead to the
  desired results when the intention is to make other widgets beneath visible.
  Instead, use Qt::WA_AlwaysStackOnTop to enable semi-transparent QOpenGLWidget
  instances with other widgets visible underneath. Keep in mind however that
  this breaks the stacking order, so it will no longer be possible to have
  other widgets on top of the QOpenGLWidget.

  \sa format(), Qt::WA_AlwaysStackOnTop, QSurfaceFormat::setDefaultFormat()
 */
void OffscreenOpenGL::setFormat(const QSurfaceFormat &format)
{
    Q_D(OffscreenOpenGL);
    if (Q_UNLIKELY(d->initialized)) {
        qWarning("QOpenGLWidget: Already initialized, setting the format has no effect");
        return;
    }
    d->requestedFormat = format;
}

/*!
    Returns the context and surface format used by this widget and its toplevel
    window.

    After the widget and its toplevel have both been created, resized and shown,
    this function will return the actual format of the context. This may differ
    from the requested format if the request could not be fulfilled by the
    platform. It is also possible to get larger color buffer sizes than
    requested.

    When the widget's window and the related OpenGL resources are not yet
    initialized, the return value is the format that has been set via
    setFormat().

    \sa setFormat(), context()
 */
QSurfaceFormat OffscreenOpenGL::format() const
{
    Q_D(const OffscreenOpenGL);
    return d->initialized ? d->context->format() : d->requestedFormat;
}

/*!
    Sets a custom internal texture format of \a texFormat.

    When working with sRGB framebuffers, it will be necessary to specify a
    format like \c{GL_SRGB8_ALPHA8}. This can be achieved by calling this
    function.

    \note This function has no effect if called after the widget has already
    been shown and thus it performed initialization.

    \note This function will typically have to be used in combination with a
    QSurfaceFormat::setDefaultFormat() call that sets the color space to
    QSurfaceFormat::sRGBColorSpace.

    \since 5.10
 */
void OffscreenOpenGL::setTextureFormat(GLenum texFormat)
{
    Q_D(OffscreenOpenGL);
    if (Q_UNLIKELY(d->initialized)) {
        qWarning("QOpenGLWidget: Already initialized, setting the internal texture format has no effect");
        return;
    }

    d->textureFormat = texFormat;
}

/*!
    \return the active internal texture format if the widget has already
    initialized, the requested format if one was set but the widget has not yet
    been made visible, or \nullptr if setTextureFormat() was not called and the
    widget has not yet been made visible.

    \since 5.10
 */
GLenum OffscreenOpenGL::textureFormat() const
{
    Q_D(const OffscreenOpenGL);
    return d->textureFormat;
}

/*!
  \return \e true if the widget and OpenGL resources, like the context, have
  been successfully initialized. Note that the return value is always false
  until the widget is shown.
*/
bool OffscreenOpenGL::isValid() const
{
    Q_D(const OffscreenOpenGL);
    return d->initialized && d->subject && d->context->isValid();
}

/*!
  Prepares for rendering OpenGL content for this widget by making the
  corresponding context current and binding the framebuffer object in that
  context.

  It is not necessary to call this function in most cases, because it
  is called automatically before invoking paintGL().

  \sa context(), paintGL(), doneCurrent()
 */
void OffscreenOpenGL::makeCurrent()
{
    Q_D(OffscreenOpenGL);
    if (!d->initialized)
        return;

    d->context->makeCurrent(d->surface);

    if (d->fbo) // there may not be one if we are in reset()
        d->fbo->bind();

}

/*!
  Releases the context.

  It is not necessary to call this function in most cases, since the
  widget will make sure the context is bound and released properly
  when invoking paintGL().
 */
void OffscreenOpenGL::doneCurrent()
{
    Q_D(OffscreenOpenGL);
    if (!d->initialized)
        return;
    d->context->doneCurrent();
}

/*!
  \return The QOpenGLContext used by this widget or \c 0 if not yet initialized.

  \note The context and the framebuffer object used by the widget changes when
  reparenting the widget via setParent().

  \sa QOpenGLContext::setShareContext(), defaultFramebufferObject()
 */
QOpenGLContext *OffscreenOpenGL::context() const
{
    Q_D(const OffscreenOpenGL);
    return d->context;
}

/*!
  \return The framebuffer object handle or \c 0 if not yet initialized.

  \note The framebuffer object belongs to the context returned by context()
  and may not be accessible from other contexts.

  \note The context and the framebuffer object used by the widget changes when
  reparenting the widget via setParent(). In addition, the framebuffer object
  changes on each resize.

  \sa context()
 */
GLuint OffscreenOpenGL::defaultFramebufferObject() const
{
    Q_D(const OffscreenOpenGL);
    return d->fbo ? d->fbo->handle() : 0;
}

/*!
  Renders and returns a 32-bit RGB image of the framebuffer.
  \note This is a potentially expensive operation because it relies on glReadPixels()
  to read back the pixels. This may be slow and can stall the GPU pipeline.
*/
QImage OffscreenOpenGL::grabFramebuffer()
{
    Q_D(OffscreenOpenGL);
    return d->grabFramebuffer();
}

/*!
  Handles resize events that are passed in the \a e event parameter.

  \note Avoid overriding this function in derived classes. If that is not
  feasible, make sure that OffscreenOpenGL's implementation is invoked
  too. Otherwise the underlying framebuffer object and related resources will
  not get resized properly and will lead to incorrect rendering.
*/
void OffscreenOpenGL::resizeEvent(QResizeEvent *event)
{
    Q_D(OffscreenOpenGL);
    if (event->size().isEmpty()) {
        d->fakeHidden = true;
        return;
    }
    d->fakeHidden = false;
    d->initialize();
    if (!d->initialized)
        return;
    d->recreateFbo();
}

Q_CONSTRUCTOR_FUNCTION(qt_registerDefaultPlatformBackingStoreOpenGLSupport);

QT_END_NAMESPACE
