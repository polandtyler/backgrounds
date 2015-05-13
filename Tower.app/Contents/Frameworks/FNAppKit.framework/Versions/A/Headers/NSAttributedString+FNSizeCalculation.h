//
//  NSAttributedString+FNSizeCalculation.h
//  FNAppKit
//
//  Created by Alexander Rinass on 24/09/14.
//  Copyright (c) 2014 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSAttributedString (FNSizeCalculation)

- (NSSize)sizeWithMaximumWidth:(CGFloat)maximumWidth;
- (NSSize)sizeWithMaximumWidth:(CGFloat)maximumWidth insetSize:(NSSize)insetSize lineFragmentPadding:(CGFloat)lineFragmentPadding;

@end
