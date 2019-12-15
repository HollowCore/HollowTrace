//
//  main.c
//  HollowTrace
//
//  Created by Matt Stoker on 11/17/19.
//  Copyright © 2019 HollowCore. All rights reserved.
//

#include "../HollowMac/Source/HollowMac.h"
#include "../Source/HollowTrace.h"

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Application Callback Prototypes
//----------------------------------------------------------------------------------------------------------------------------------

void ApplicationReady(void* context, HCApplicationRef application);

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Window Callback Prototypes
//----------------------------------------------------------------------------------------------------------------------------------

void Resize(void* context, HCWindowRef window, HCSize size);
void Draw(void* context, HCRasterViewRef view, HCRasterRef raster);

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Menu Callback Prototypes
//----------------------------------------------------------------------------------------------------------------------------------

void QuitClicked(void* context, HCMenuRef menu);
void AboutClicked(void* context, HCMenuRef menu);
void MinimizeClicked(void* context, HCMenuRef menu);
void HelpClicked(void* context, HCMenuRef menu);
void ButtonClicked(void* context, HCButtonRef button);

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Global Data
//----------------------------------------------------------------------------------------------------------------------------------
HCRasterViewRef g_TraceView = NULL;

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Application Entry Point
//----------------------------------------------------------------------------------------------------------------------------------

int main(int argc, const char* argv[]) {
    HCApplicationRef application = HCApplicationCreate();
    HCApplicationRun(application, ApplicationReady, NULL);
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Application Callbacks
//----------------------------------------------------------------------------------------------------------------------------------

void ApplicationReady(void* context, HCApplicationRef application) {
    // Setup application menus
    HCMenuRef applicationMenu = HCMenuCreate();
    HCMenuRef aboutMenuItem = HCMenuCreate();
    HCMenuSetTitle(aboutMenuItem, HCStringCreateWithCString("About Tracer"));
    HCMenuSetClickCallback(aboutMenuItem, AboutClicked, application);
    HCMenuAddChildMenu(applicationMenu, aboutMenuItem);
    HCMenuRef quitMenuItem = HCMenuCreate();
    HCMenuSetTitle(quitMenuItem, HCStringCreateWithCString("Quit Tracer"));
    HCMenuSetShortcutKey(quitMenuItem, HCStringCreateWithCString("q"));
    HCMenuSetClickCallback(quitMenuItem, QuitClicked, application);
    HCMenuAddChildMenu(applicationMenu, quitMenuItem);
    HCApplicationAddMenu(application, applicationMenu);
    
    HCMenuRef windowMenu = HCMenuCreate();
    HCMenuSetTitle(windowMenu, HCStringCreateWithCString("Window"));
    HCMenuRef minimizeMenuItem = HCMenuCreate();
    HCMenuSetTitle(minimizeMenuItem, HCStringCreateWithCString("Minimize"));
    HCMenuSetShortcutKey(minimizeMenuItem, HCStringCreateWithCString("m"));
    HCMenuSetClickCallback(minimizeMenuItem, MinimizeClicked, application);
    HCMenuAddChildMenu(windowMenu, minimizeMenuItem);
    HCApplicationAddMenu(application, windowMenu);
    
    HCMenuRef helpMenu = HCMenuCreate();
    HCMenuSetTitle(helpMenu, HCStringCreateWithCString("Help"));
    HCMenuRef helpMenuItem = HCMenuCreate();
    HCMenuSetTitle(helpMenuItem, HCStringCreateWithCString("App Help"));
    HCMenuSetShortcutKey(helpMenuItem, HCStringCreateWithCString("h"));
    HCMenuSetClickCallback(helpMenuItem, HelpClicked, application);
    HCMenuAddChildMenu(helpMenu, helpMenuItem);
    HCApplicationAddMenu(application, helpMenu);
    
    // Setup application window and UI
    HCWindowRef window = HCWindowCreate();
    HCWindowSetResizeCallback(window, Resize, NULL);
    
    g_TraceView = HCRasterViewCreate();
    HCViewSetFrame((HCViewRef)g_TraceView, HCRectangleMake(HCPointZero, HCWindowSize(window)));
    HCViewSetBackgroundColor((HCViewRef)g_TraceView, HCColorGreen);
    HCRasterViewSetDrawCallback(g_TraceView, Draw, NULL);
    HCViewAddChildView(HCWindowContentView(window), (HCViewRef)g_TraceView);
    
    HCWindowDisplay(window);
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Window Callbacks
//----------------------------------------------------------------------------------------------------------------------------------

void Resize(void* context, HCWindowRef window, HCSize size) {
    printf("Resize Sent! (%f,%f)\n", size.width, size.height);
    HCViewSetFrame((HCViewRef)g_TraceView, HCRectangleMake(HCPointZero, size));
}

void Draw(void* context, HCRasterViewRef view, HCRasterRef raster) {
    HCSetRef objects = HCSetCreate();
    HCSetAddObjectReleased(objects, HCSphereCreate(HCVectorMake(0.0, 0.0, 0.0), 0.5));
    
    HCVector cameraOrigin = HCVectorMake(0.0, 0.0, 1.0);
    HCVector cameraTarget = HCVectorMake(0.0, 0.0, 0.0);
    HCVector cameraUp = HCVectorMake(0.0, 1.0, 0.0);
    
    HCVector cameraKAxis = HCVectorNormalize(HCVectorSubtract(cameraTarget, cameraOrigin));
    HCVector cameraIAxis = HCVectorNormalize(HCVectorCross(cameraKAxis, cameraUp));
    HCVector cameraJAxis = HCVectorNormalize(HCVectorCross(cameraIAxis, cameraKAxis));
    HCReal cameraFieldOfView = M_PI * 0.75;
    HCReal cameraAspectRatio = (HCReal)HCRasterWidth(raster) / (HCReal)HCRasterHeight(raster);
    
    HCVector cameraViewU = HCVectorScale(cameraIAxis, tanf(cameraFieldOfView * 0.5f));
    HCVector cameraViewV = HCVectorScale(cameraJAxis, HCVectorMagnitude(cameraViewU) / cameraAspectRatio);

    for (HCInteger yIndex = 0; yIndex < HCRasterHeight(raster); yIndex++) {
        for (HCInteger xIndex = 0; xIndex < HCRasterWidth(raster); xIndex++) {
            HCReal pointU = ((((HCReal)xIndex + 0.5) / (HCReal)HCRasterWidth(raster)) - 0.5) * 2.0;
            HCReal pointV = ((((HCReal)yIndex + 0.5) / (HCReal)HCRasterHeight(raster)) - 0.5) * 2.0;
            HCVector direction = HCVectorAdd(cameraKAxis, HCVectorAdd(HCVectorScale(cameraViewU, pointU), HCVectorScale(cameraViewV, pointV)));
            HCRay r = HCRayMake(cameraOrigin, direction);
            HCColor c = HCColorBlack;
            for (HCSetIterator i = HCSetIterationBegin(objects); !HCSetIterationHasEnded(&i); HCSetIterationNext(&i)) {
                HCPrimitiveRef object = i.object;
                // TODO: How to call sub-class polymorphic function? Need HCObjectType() call?
                if (!isnan(HCSphereIntersect((HCSphereRef)object, r))) {
                    c = HCColorWhite;
                }
            }
            HCRasterSetPixelAt(raster, xIndex, yIndex, c);
        }
    }
    
    HCRelease(objects);
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Menu Callbacks
//----------------------------------------------------------------------------------------------------------------------------------

void QuitClicked(void* context, HCMenuRef menu) {
    HCApplicationRef application = context;
    HCApplicationTerminate(application);
}

void AboutClicked(void* context, HCMenuRef menu) {
    printf("About Clicked!\n");
}

void MinimizeClicked(void* context, HCMenuRef menu) {
    printf("Minimize Clicked!\n");
}

void HelpClicked(void* context, HCMenuRef menu) {
    printf("Help Clicked!\n");
}

void ButtonClicked(void* context, HCButtonRef button) {
    printf("Button Clicked!\n");
    HCViewRef parent = HCViewParentViewRetained((HCViewRef)button);
    HCViewSetFrame(parent, HCRectangleOffset(HCViewFrame(parent), 1.0, 0.0));
    HCViewSetBackgroundColor(parent, HCColorGreen);
    HCRelease(parent);
    
    HCViewRef a = HCViewParentViewRetained(parent);
    HCViewRef b = HCViewChildViewAtIndexRetained(a, HCViewChildViewCount(a) - 1);
    HCViewSetFrame(b, HCRectangleInset(HCViewFrame(b), 1.0, 1.0));
    HCRelease(a);
}
