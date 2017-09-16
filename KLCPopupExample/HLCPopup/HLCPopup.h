// HLCPopup.h
//
// Created by Jeff Mascia
// Copyright (c) 2013-2014 Kullect Inc. (http://kullect.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.


// HLCPopupShowType: Controls how the popup will be presented.
typedef NS_ENUM (NSInteger, HLCPopupShowType) {
    HLCPopupShowTypeNone = 0,
    HLCPopupShowTypeFadeIn,
    HLCPopupShowTypeGrowIn,
    HLCPopupShowTypeShrinkIn,
    HLCPopupShowTypeSlideInFromTop,
    HLCPopupShowTypeSlideInFromBottom,
    HLCPopupShowTypeSlideInFromLeft,
    HLCPopupShowTypeSlideInFromRight,
    HLCPopupShowTypeBounceIn,
    HLCPopupShowTypeBounceInFromTop,
    HLCPopupShowTypeBounceInFromBottom,
    HLCPopupShowTypeBounceInFromLeft,
    HLCPopupShowTypeBounceInFromRight,
    HLCPopupShowTypeHangFromTop,
};

// HLCPopupDismissType: Controls how the popup will be dismissed.
typedef NS_ENUM (NSInteger, HLCPopupDismissType) {
    HLCPopupDismissTypeNone = 0,
    HLCPopupDismissTypeFadeOut,
    HLCPopupDismissTypeGrowOut,
    HLCPopupDismissTypeShrinkOut,
    HLCPopupDismissTypeSlideOutToTop,
    HLCPopupDismissTypeSlideOutToBottom,
    HLCPopupDismissTypeSlideOutToLeft,
    HLCPopupDismissTypeSlideOutToRight,
    HLCPopupDismissTypeBounceOut,
    HLCPopupDismissTypeBounceOutToTop,
    HLCPopupDismissTypeBounceOutToBottom,
    HLCPopupDismissTypeBounceOutToLeft,
    HLCPopupDismissTypeBounceOutToRight,
    HLCPopupDismissTypeHangToBottom,
};



// HLCPopupHorizontalLayout: Controls where the popup will come to rest horizontally.
typedef NS_ENUM (NSInteger, HLCPopupHorizontalLayout) {
    HLCPopupHorizontalLayoutCustom = 0,
    HLCPopupHorizontalLayoutLeft,
    HLCPopupHorizontalLayoutLeftOfCenter,
    HLCPopupHorizontalLayoutCenter,
    HLCPopupHorizontalLayoutRightOfCenter,
    HLCPopupHorizontalLayoutRight,
};

// HLCPopupVerticalLayout: Controls where the popup will come to rest vertically.
typedef NS_ENUM (NSInteger, HLCPopupVerticalLayout) {
    HLCPopupVerticalLayoutCustom = 0,
    HLCPopupVerticalLayoutTop,
    HLCPopupVerticalLayoutAboveCenter,
    HLCPopupVerticalLayoutCenter,
    HLCPopupVerticalLayoutBelowCenter,
    HLCPopupVerticalLayoutBottom,
};

// HLCPopupMaskType
typedef NS_ENUM (NSInteger, HLCPopupMaskType) {
    HLCPopupMaskTypeNone = 0,     // Allow interaction with underlying views.
    HLCPopupMaskTypeClear,     // Don't allow interaction with underlying views.
    HLCPopupMaskTypeDimmed,     // Don't allow interaction with underlying views, dim background.
};

//Popup出现的层级，值越大，层级越低；HLCPopupLevelNormal表示出现在最顶层
typedef NS_ENUM(NSUInteger, HLCPopupLevel) {
    HLCPopupLevelNormal = 0,
    HLCPopupLevelLow
};

// HLCPopupLayout structure and maker functions
struct HLCPopupLayout {
    HLCPopupHorizontalLayout horizontal;
    HLCPopupVerticalLayout vertical;
};
typedef struct HLCPopupLayout   HLCPopupLayout;

extern HLCPopupLayout HLCPopupLayoutMake(HLCPopupHorizontalLayout horizontal, HLCPopupVerticalLayout vertical);

extern const HLCPopupLayout HLCPopupLayoutCenter;



@interface HLCPopup : UIView

// This is the view that you want to appear in Popup.
// - Must provide contentView before or in willStartShowing.
// - Must set desired size of contentView before or in willStartShowing.
@property (nonatomic, strong) UIView *contentView;

// Animation transition for presenting contentView. default = shrink in
@property (nonatomic, assign) HLCPopupShowType showType;

// Animation transition for dismissing contentView. default = shrink out
@property (nonatomic, assign) HLCPopupDismissType dismissType;

// Mask prevents background touches from passing to underlying views. default = dimmed.
@property (nonatomic, assign) HLCPopupMaskType maskType;

// If YES, then popup will get dismissed when background is touched. default = YES.
@property (nonatomic, assign) BOOL shouldDismissOnBackgroundTouch;

// If YES, then popup will get dismissed when content view is touched. default = NO.
@property (nonatomic, assign) BOOL shouldDismissOnContentTouch;

// Block gets called after show animation finishes. Be sure to use weak reference for popup within the block to avoid retain cycle.
@property (nonatomic, copy) void(^didFinishShowingCompletion)();

// Block gets called when dismiss animation starts. Be sure to use weak reference for popup within the block to avoid retain cycle.
@property (nonatomic, copy) void(^willStartDismissingCompletion)();

// Block gets called after dismiss animation finishes. Be sure to use weak reference for popup within the block to avoid retain cycle.
@property (nonatomic, copy) void(^didFinishDismissingCompletion)();

// Convenience method for creating popup with custom values.
+ (instancetype)popupWithContentView:(UIView *)contentView
                            showType:(HLCPopupShowType)showType
                         dismissType:(HLCPopupDismissType)dismissType
                            maskType:(HLCPopupMaskType)maskType
            dismissOnBackgroundTouch:(BOOL)shouldDismissOnBackgroundTouch
               dismissOnContentTouch:(BOOL)shouldDismissOnContentTouch;

// Dismisses all the popups in the app. Use as a fail-safe for cleaning up.
+ (void)dismissAllPopups;

// Show popup with center layout. Animation determined by showType.
- (void)show;

// Show with specified layout.
- (void)showWithLayout:(HLCPopupLayout)layout;

// Show and then dismiss after duration. 0.0 or less will be considered infinity.
- (void)showWithDuration:(NSTimeInterval)duration;

// Show with layout and dismiss after duration.
- (void)showWithLayout:(HLCPopupLayout)layout duration:(NSTimeInterval)duration;

// Show centered at point in view's coordinate system. If view is nil use screen base coordinates.
- (void)showAtCenter:(CGPoint)center inView:(UIView *)view;

// Show centered at point in view's coordinate system, then dismiss after duration.
- (void)showAtCenter:(CGPoint)center inView:(UIView *)view withDuration:(NSTimeInterval)duration;

// Dismiss popup. Uses dismissType if animated is YES.
- (void)dismiss:(BOOL)animated;

/*
 * 标识popup弹窗出现的层级，0表示在最顶层，1表示在第二层（最上层还有个Popup），以此类推
 */
@property (nonatomic, assign) HLCPopupLevel popupLevel;

#pragma mark Subclassing
@property (nonatomic, strong, readonly) UIView *backgroundView;
@property (nonatomic, strong, readonly) UIView *containerView;
@property (nonatomic, assign, readonly) BOOL isBeingShown;
@property (nonatomic, assign, readonly) BOOL isShowing;
@property (nonatomic, assign, readonly) BOOL isBeingDismissed;

- (void)willStartShowing;
- (void)willStartAnimating;
- (void)didFinishShowing;
- (void)willStartDismissing;
- (void)didFinishDismissing;

@end


#pragma mark - UIView Category

@interface UIView (HLCPopup)
- (void)forEachPopupDoBlock:(void (^)(HLCPopup *popup))block;
- (void)dismissPresentingPopup;
@end

