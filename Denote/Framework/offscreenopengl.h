#ifndef OFFSCREENOPENGL_H
#define OFFSCREENOPENGL_H

#include <QPainter>
#include <QtGui/QSurfaceFormat>
#include <QtGui/qopengl.h>
#include <QWidget>

QT_BEGIN_NAMESPACE

class OffscreenOpenGLPrivate;

class OffscreenOpenGL : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(OffscreenOpenGL)

public:
    enum UpdateBehavior {
        NoPartialUpdate,
        PartialUpdate
    };

    explicit OffscreenOpenGL(QWidget* subject);
    ~OffscreenOpenGL();

    void setSubject(QWidget* subject);
    QWidget* subject() const;

    void setPainter(QPainter* painter);
    QPaintDevice* paintDevice() const;

    void setUpdateBehavior(UpdateBehavior updateBehavior);
    UpdateBehavior updateBehavior() const;

    void setFormat(const QSurfaceFormat &format);
    QSurfaceFormat format() const;

    GLenum textureFormat() const;
    void setTextureFormat(GLenum texFormat);

    bool isValid() const;

    void makeCurrent();
    void doneCurrent();

    QOpenGLContext *context() const;
    GLuint defaultFramebufferObject() const;

    QImage grabFramebuffer();

    void resizeEvent(QResizeEvent* event);

signals:
    void aboutToCompose();
    void frameSwapped();
    void aboutToResize();
    void resized();

private:
    Q_DISABLE_COPY(OffscreenOpenGL)
};

QT_END_NAMESPACE

#endif // OFFSCREENOPENGL_H
