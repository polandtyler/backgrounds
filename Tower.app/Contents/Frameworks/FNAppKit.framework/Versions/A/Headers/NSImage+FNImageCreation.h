//
//  NSImage+FNImageCreation.h
//  FNAppKit
//
//  Created by Alexander Rinass on 30/09/14.
//  Copyright (c) 2014 Fournova GmbH. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface NSImage (FNImageCreation)

+ (NSImage *)imageWithData:(NSData *)imageData scale:(CGFloat)scaleFactor;

@end
