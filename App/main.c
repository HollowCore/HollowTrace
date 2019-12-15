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
// MARK: - UI Action Callback Prototypes
//----------------------------------------------------------------------------------------------------------------------------------

void QuitClicked(void* context, HCMenuRef menu);
void AboutClicked(void* context, HCMenuRef menu);
void MinimizeClicked(void* context, HCMenuRef menu);
void HelpClicked(void* context, HCMenuRef menu);
void LeftClicked(void* context, HCButtonRef button);
void RightClicked(void* context, HCButtonRef button);
void ForwardClicked(void* context, HCButtonRef button);
void BackwardClicked(void* context, HCButtonRef button);

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Global Data
//----------------------------------------------------------------------------------------------------------------------------------

HCRasterViewRef g_TraceView = NULL;
HCVector g_CameraPosition = { .x = 0.0, .y = 0.0, .z = 1.0 };

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
    HCViewSetBackgroundColor((HCViewRef)g_TraceView, HCColorGreen);
    HCRasterViewSetDrawCallback(g_TraceView, Draw, NULL);
    HCViewAddChildView(HCWindowContentView(window), (HCViewRef)g_TraceView);
    
    HCButtonRef leftButton = HCButtonCreate();
    HCViewSetFrame((HCViewRef)leftButton, HCRectangleMake(HCPointMake(10.0, 40.0), HCSizeMake(100.0, 30.0)));
    HCButtonSetTitle(leftButton, HCStringCreateWithCString("<-"));
    HCButtonSetClickCallback(leftButton, LeftClicked, NULL);
    HCViewAddChildView((HCViewRef)g_TraceView, (HCViewRef)leftButton);
    
    HCButtonRef rightButton = HCButtonCreate();
    HCViewSetFrame((HCViewRef)rightButton, HCRectangleMake(HCPointMake(110.0, 40.0), HCSizeMake(100.0, 30.0)));
    HCButtonSetTitle(rightButton, HCStringCreateWithCString("->"));
    HCButtonSetClickCallback(rightButton, RightClicked, NULL);
    HCViewAddChildView((HCViewRef)g_TraceView, (HCViewRef)rightButton);
    
    HCButtonRef forwardButton = HCButtonCreate();
    HCViewSetFrame((HCViewRef)forwardButton, HCRectangleMake(HCPointMake(60.0, 10.0), HCSizeMake(100.0, 30.0)));
    HCButtonSetTitle(forwardButton, HCStringCreateWithCString("^"));
    HCButtonSetClickCallback(forwardButton, ForwardClicked, NULL);
    HCViewAddChildView((HCViewRef)g_TraceView, (HCViewRef)forwardButton);
    
    HCButtonRef backwardButton = HCButtonCreate();
    HCViewSetFrame((HCViewRef)backwardButton, HCRectangleMake(HCPointMake(60.0, 70.0), HCSizeMake(100.0, 30.0)));
    HCButtonSetTitle(backwardButton, HCStringCreateWithCString("v"));
    HCButtonSetClickCallback(backwardButton, BackwardClicked, NULL);
    HCViewAddChildView((HCViewRef)g_TraceView, (HCViewRef)backwardButton);
    
    HCWindowDisplay(window);
    
    HCViewSetFrame((HCViewRef)g_TraceView, HCRectangleMake(HCPointZero, HCViewSize(HCWindowContentView(window))));
}

//----------------------------------------------------------------------------------------------------------------------------------
// MARK: - Window Callbacks
//----------------------------------------------------------------------------------------------------------------------------------

void Resize(void* context, HCWindowRef window, HCSize contentSize) {
    printf("Resize Sent! (%f,%f)\n", contentSize.width, contentSize.height);
//    HCViewSetFrame((HCViewRef)g_TraceView, HCRectangleMake(HCPointZero, contentSize));
}

void Draw(void* context, HCRasterViewRef view, HCRasterRef raster) {
    HCSetRef objects = HCSetCreate();
    HCSetAddObjectReleased(objects, HCSphereCreate(HCVectorMake(0.0, 0.0, 0.0), 0.5));
    
    HCVector cameraOrigin = g_CameraPosition;
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
// MARK: - UI Action Callbacks
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
    HCViewSetFrame((HCViewRef)g_TraceView, HCRectangleInset(HCViewFrame((HCViewRef)g_TraceView), 10.0, 10.0));
}

void HelpClicked(void* context, HCMenuRef menu) {
    printf("Help Clicked!\n");
}

void LeftClicked(void* context, HCButtonRef button) {
    printf("Left Clicked!\n");
    g_CameraPosition = HCVectorAdd(g_CameraPosition, HCVectorScale(HCVectorMake(1.0, 0.0, 0.0), 1.0));
    HCViewDraw((HCViewRef)g_TraceView);
}

void RightClicked(void* context, HCButtonRef button) {
    printf("Right Clicked!\n");
    g_CameraPosition = HCVectorAdd(g_CameraPosition, HCVectorScale(HCVectorMake(0.0, 0.0, 1.0), 1.0));
    HCViewDraw((HCViewRef)g_TraceView);
}

void ForwardClicked(void* context, HCButtonRef button) {
    printf("Forward Clicked!\n");
    g_CameraPosition = HCVectorAdd(g_CameraPosition, HCVectorScale(HCVectorNormalize(HCVectorSubtract(HCVectorZero, g_CameraPosition)), 1.0));
    HCViewDraw((HCViewRef)g_TraceView);
}

void BackwardClicked(void* context, HCButtonRef button) {
    printf("Backward Clicked!\n");
    g_CameraPosition = HCVectorAdd(g_CameraPosition, HCVectorScale(HCVectorNormalize(HCVectorSubtract(HCVectorZero, g_CameraPosition)), -1.0));
    HCViewDraw((HCViewRef)g_TraceView);
}
