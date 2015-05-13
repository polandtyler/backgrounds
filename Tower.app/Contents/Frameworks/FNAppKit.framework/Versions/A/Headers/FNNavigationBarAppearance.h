//
//  FNNavigationBarAppearance.h
//  FNAppKit
//
//  Created by Alexander Rinass on 14.06.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import "FNViewAppearance.h"

@interface FNNavigationBarAppearance : FNViewAppearance
@property (nonatomic) CGFloat barHeight;
@property (nonatomic) NSGradient *backgroundGradient;
@property (nonatomic) NSImage *backgroundImage;
@property (nonatomic) NSShadow *shadow;
@property (nonatomic) CGFloat shadowHeight;
@property (nonatomic) BOOL displayTopBorder;
@property (nonatomic) BOOL displayBottomBorder;
@property (nonatomic) NSColor *topBorderColor;
@property (nonatomic) NSColor *bottomBorderColor;

+ (id)defaultAppearance;

- (void)setBackgroundImage:(NSImage *)backgroundImage autoUpdateBarHeight:(BOOL)autoUpdateBarHeight;

@end
