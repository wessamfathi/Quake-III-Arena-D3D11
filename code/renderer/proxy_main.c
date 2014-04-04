#include "tr_local.h"
#include "proxy_main.h"

// D3D headers
#include "d3d_public.h"

// GL headers
#include "gl_common.h"
#include "gl_image.h"

// @pjb: this is just here to deliberately fuck the build if driver is used in here
#define driver #driver_disallowed

// called before the library is unloaded
// if the system is just reconfiguring, pass destroyWindow = qfalse,
// which will keep the screen from flashing to the desktop.
void	PROXY_Shutdown( qboolean destroyWindow ) {
    RE_Shutdown( destroyWindow );
    // @pjb todo
}

// All data that will be used in a level should be
// registered before rendering any frames to prevent disk hits,
// but they can still be registered at a later time
// if necessary.
//
// BeginRegistration makes any existing media pointers invalid
// and returns the current gl configuration, including screen width
// and height, which can be used by the client to intelligently
// size display elements
void	PROXY_BeginRegistration( glconfig_t *config ) {
    RE_BeginRegistration( config );
    // @pjb todo
}

qhandle_t PROXY_RegisterModel( const char *name ) {
    qhandle_t gl, dx;
    gl = RE_RegisterModel( name );

    // @pjb todo - we may have to proxy all these handles too?
    dx = gl;

    if (dx != gl) {
        Com_Error( ERR_FATAL, "[PROXY DRIVER] RegisterModel() returning conflicting results: %d vs %d\n", gl, dx);
    }
    return dx;
}

qhandle_t PROXY_RegisterSkin( const char *name ) {
    qhandle_t gl, dx;
    gl = RE_RegisterSkin( name );

    // @pjb todo - we may have to proxy all these handles too?
    dx = gl;

    if (dx != gl) {
        Com_Error( ERR_FATAL, "[PROXY DRIVER] RegisterModel() returning conflicting results: %d vs %d\n", gl, dx);
    }
    return dx;
}

qhandle_t PROXY_RegisterShader( const char *name ) {
    qhandle_t gl, dx;
    gl = RE_RegisterShader( name );

    // @pjb todo - we may have to proxy all these handles too?
    dx = gl;

    if (dx != gl) {
        Com_Error( ERR_FATAL, "[PROXY DRIVER] RegisterModel() returning conflicting results: %d vs %d\n", gl, dx);
    }
    return dx;
}

qhandle_t PROXY_RegisterShaderNoMip( const char *name ) {
    qhandle_t gl, dx;
    gl = RE_RegisterShaderNoMip( name );

    // @pjb todo - we may have to proxy all these handles too?
    dx = gl;

    if (dx != gl) {
        Com_Error( ERR_FATAL, "[PROXY DRIVER] RegisterModel() returning conflicting results: %d vs %d\n", gl, dx);
    }
    return dx;
}

void	PROXY_LoadWorld( const char *name ) {


    RE_LoadWorldMap( name );
    // @pjb todo
}

// the vis data is a large enough block of data that we go to the trouble
// of sharing it with the clipmodel subsystem
void	PROXY_SetWorldVisData( const byte *vis ) {

    RE_SetWorldVisData( vis );
    // @pjb todo
}

// EndRegistration will draw a tiny polygon with each texture, forcing
// them to be loaded into card memory
void	PROXY_EndRegistration( void ) {

    extern void RE_EndRegistration( void );

    RE_EndRegistration();
    // @pjb todo
}

// a scene is built up by calls to R_ClearScene and the various R_Add functions.
// Nothing is drawn until R_RenderScene is called.
void	PROXY_ClearScene( void ) {
    RE_ClearScene();
    // @pjb todo
}

void	PROXY_AddRefEntityToScene( const refEntity_t *re ) {
    RE_AddRefEntityToScene( re );
    // @pjb todo
}

void	PROXY_AddPolyToScene( qhandle_t hShader , int numVerts, const polyVert_t *verts, int num ) {
    RE_AddPolyToScene( hShader, numVerts, verts, num );
    // @pjb todo
}

int		PROXY_LightForPoint( vec3_t point, vec3_t ambientLight, vec3_t directedLight, vec3_t lightDir ) {
    int gl, dx;
    
    gl = R_LightForPoint( point, ambientLight, directedLight, lightDir );
    
    // @pjb todo
    dx = gl;

    if (dx != gl) {
        Com_Error( ERR_FATAL, "[PROXY DRIVER] LightForPoint() returning conflicting results: %d vs %d\n", gl, dx);
    }

    return dx;
}

void	PROXY_AddLightToScene( const vec3_t org, float intensity, float r, float g, float b ) {
    RE_AddLightToScene( org, intensity, r, g, b );
    // @pjb todo
}

void	PROXY_AddAdditiveLightToScene( const vec3_t org, float intensity, float r, float g, float b ) {
    RE_AddAdditiveLightToScene( org, intensity, r, g, b );
    // @pjb todo
}

void	PROXY_RenderScene( const refdef_t *fd ) {
    RE_RenderScene( fd );
    // @pjb todo
}

// NULL = 1,1,1,1
void	PROXY_SetColor( const float *rgba ) {
    RE_SetColor( rgba );
    // @pjb todo
}

// 0 = white
void	PROXY_DrawStretchPic ( float x, float y, float w, float h, 
	float s1, float t1, float s2, float t2, qhandle_t hShader ) {

    RE_StretchPic( x, y, w, h, s1, t1, s2, t2, hShader );
    // @pjb todo
}	

// Draw images for cinematic rendering, pass as 32 bit rgba
void	PROXY_DrawStretchRaw (int x, int y, int w, int h, int cols, int rows, const byte *data, int client, qboolean dirty) {

    RE_StretchRaw( x, y, w, h, cols, rows, data, client, dirty );
    // @pjb todo
}

void	PROXY_UploadCinematic (int w, int h, int cols, int rows, const byte *data, int client, qboolean dirty) {

    RE_UploadCinematic( w, h, cols, rows, data, client, dirty );
    // @pjb todo
}

void	PROXY_BeginFrame( stereoFrame_t stereoFrame ) {

    RE_BeginFrame( stereoFrame );
    // @pjb todo
}

// if the pointers are not NULL, timing info will be returned
void	PROXY_EndFrame( int *frontEndMsec, int *backEndMsec ) {

    int glFrontMS, glBackMS;
    int dxFrontMS, dxBackMS;

    RE_EndFrame( &glFrontMS, &glBackMS );

    // @pjb todo
    dxFrontMS = 0;
    dxBackMS = 0;

    if ( frontEndMsec )
        *frontEndMsec = max(glFrontMS, dxFrontMS);

    if ( backEndMsec )
        *backEndMsec = max(glBackMS, dxBackMS);
}

void	PROXY_RegisterFont(const char *fontName, int pointSize, fontInfo_t *font) {

    RE_RegisterFont( fontName, pointSize, font );
    // @pjb todo
}

void PROXY_CreateImage( const image_t* image, const byte *pic, qboolean isLightmap )
{
    GL_CreateImage( image, pic, isLightmap );
    // @pjb todo
}

void PROXY_DeleteImage( const image_t* image )
{
    GL_DeleteImage( image );
    // @pjb todo
}

imageFormat_t PROXY_GetImageFormat( const image_t* image )
{
    // Just do the GL one
    return GL_GetImageFormat( image );
}

void PROXY_SetGamma( unsigned char red[256], unsigned char green[256], unsigned char blue[256] )
{
    GLRB_SetGamma( red, green, blue );
    // @pjb: todo
}

int PROXY_SumOfUsedImages( void )
{
    return GL_SumOfUsedImages(); 
    // @pjb: todo
}

void PROXY_GetExports( refexport_t* re )
{
	re->Shutdown = PROXY_Shutdown;

	re->BeginRegistration = PROXY_BeginRegistration;
	re->RegisterModel = PROXY_RegisterModel;
	re->RegisterSkin = PROXY_RegisterSkin;
	re->RegisterShader = PROXY_RegisterShader;
	re->RegisterShaderNoMip = PROXY_RegisterShaderNoMip;
	re->LoadWorld = PROXY_LoadWorld;
	re->SetWorldVisData = PROXY_SetWorldVisData;
	re->EndRegistration = PROXY_EndRegistration;

	re->BeginFrame = PROXY_BeginFrame;
	re->EndFrame = PROXY_EndFrame;

	re->MarkFragments = R_MarkFragments;
	re->LerpTag = R_LerpTag;
	re->ModelBounds = R_ModelBounds;

	re->ClearScene = PROXY_ClearScene;
	re->AddRefEntityToScene = PROXY_AddRefEntityToScene;
	re->AddPolyToScene = PROXY_AddPolyToScene;
	re->LightForPoint = R_LightForPoint;
	re->AddLightToScene = PROXY_AddLightToScene;
	re->AddAdditiveLightToScene = PROXY_AddAdditiveLightToScene;
	re->RenderScene = PROXY_RenderScene;

	re->SetColor = PROXY_SetColor;
	re->DrawStretchPic = PROXY_DrawStretchPic;
	re->DrawStretchRaw = PROXY_DrawStretchRaw;
	re->UploadCinematic = PROXY_UploadCinematic;

	re->RegisterFont = PROXY_RegisterFont;
	re->RemapShader = R_RemapShader;          // @pjb: TODO - check these?
	re->GetEntityToken = R_GetEntityToken;    // @pjb: TODO - check these?
	re->inPVS = R_inPVS;                      // @pjb: TODO - check these?
}

graphicsDriver_t* PROXY_DriverInit( void )
{
    static graphicsDriver_t proxyDriver = {
        PROXY_CreateImage,
        PROXY_DeleteImage,
        PROXY_GetImageFormat,
        PROXY_SetGamma,
        PROXY_SumOfUsedImages
    };

    return &proxyDriver;
}
