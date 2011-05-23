#ifndef SCREEN_MULTI_VIEWER_H
#define SCREEN_MULTI_VIEWER_H

#define GL_GLEXT_PROTOTYPES

#include <kernel/ScreenBase.h>

#include <osg/Program>
#include <osg/Shader>
#include <osg/Polytope>

#include <osg/Camera>

namespace cvr
{

class ScreenMultiViewer : public ScreenBase
{
    public:
        ScreenMultiViewer();
        virtual ~ScreenMultiViewer();

        virtual void init(int mode = 0);

        virtual void computeViewProj();
        virtual void updateCamera();

        virtual void setClearColor(osg::Vec4 color);
        virtual ScreenInfo * findScreenInfo(osg::Camera * c);

        struct FrustumPoints
        {
            osg::Vec3 nearTL;
            osg::Vec3 nearTR;
            osg::Vec3 nearBL;
            osg::Vec3 nearBR;
            osg::Vec3 farTL;
            osg::Vec3 farTR;
            osg::Vec3 farBL;
            osg::Vec3 farBR;
        };

        void computeDefaultViewProj(osg::Vec3d eyePos, osg::Matrix & view, osg::Matrix & proj, float & dist, struct FrustumPoints & fp, osg::Vec3 & viewerScreenPos);

        struct PreDrawCallback : public osg::Camera::DrawCallback
        {
            enum IndexState
            {
                FIXED = 0,
                TOGGLE
            };

            virtual void operator()(osg::RenderInfo & ri) const;
            ScreenMultiViewer * _screen;
            mutable int _index;
            IndexState _indexState;
            mutable bool _init;
            mutable bool first;
            mutable GLuint _query;
        };

        struct PostDrawCallback : public osg::Camera::DrawCallback
        {
            virtual void operator()(osg::RenderInfo & ri) const;
            PreDrawCallback * _pdc;
            ScreenMultiViewer * _screen;
            mutable bool first;
        };

        struct StereoIdentCallback : public osgUtil::SceneView::ComputeStereoMatricesCallback
        {
                virtual osg::Matrixd
                        computeLeftEyeProjection(const osg::Matrixd &projection) const { return osg::Matrixd(); }
                virtual osg::Matrixd
                        computeLeftEyeView(const osg::Matrixd &view) const { return osg::Matrixd(); }
                virtual osg::Matrixd
                        computeRightEyeProjection(
                                                  const osg::Matrixd &projection) const { return osg::Matrixd(); }
                virtual osg::Matrixd
                        computeRightEyeView(const osg::Matrixd &view) const { return osg::Matrixd(); }
        };

    protected:
        void algtest();
        void addTestGeometry();
        void calcScreenMinMaxRatio();
        float getRatio(float x, float y, int eyeNum = 0);

        osg::Vec3 _corner;
        osg::Vec3 _rightPer;
        osg::Vec3 _upPer;
        osg::Vec3 _dir0;
        osg::Vec3 _dir1;

        FrustumPoints _viewer0Frustum[2];
        FrustumPoints _viewer1Frustum[2];
        osg::Vec3 _viewer0ScreenPos[2];
        osg::Vec3 _viewer1ScreenPos[2];
        osg::Polytope _cullFrustumNear[2];
        osg::Polytope _cullFrustumFar[2];

        float _maxRatioLocal[2];
        float _minRatioLocal[2];

        osg::Uniform * _maxRatio;
        osg::Uniform * _minRatio;


        bool _testGeoAdded;
        int _frameDelay;

        osg::ref_ptr<osg::Camera> _camera;

        osg::DisplaySettings::StereoMode _stereoMode;

        osg::Matrix _view;                  ///< view matrix
        osg::Matrix _proj;

        osg::Program * _program;
        osg::Shader * _vert;
        osg::Shader * _frag;
        osg::Shader * _geom;

        osg::Uniform * _screenCorner;
        osg::Uniform * _upPerPixel;
        osg::Uniform * _rightPerPixel;

        osg::Uniform * _viewer0Pos;
        osg::Uniform * _viewer1Pos;
        osg::Uniform * _viewer0Dir;
        osg::Uniform * _viewer1Dir;

        osg::Uniform * _viewportWidth;
        osg::Uniform * _viewportHeight;
        osg::Uniform * _nearUni;
        osg::Uniform * _farUni;

        osg::Uniform * _viewer0Dist;
        osg::Uniform * _viewer1Dist;

        float _viewer0DistLocal[2];
        float _viewer1DistLocal[2];

        osg::Vec3 _viewer0PosLocal[2];
        osg::Vec3 _viewer1PosLocal[2];

        osg::Matrix _viewer0View[2];
        osg::Matrix _viewer0Proj[2];
        osg::Matrix _viewer1View[2];
        osg::Matrix _viewer1Proj[2];
};

}

#endif
