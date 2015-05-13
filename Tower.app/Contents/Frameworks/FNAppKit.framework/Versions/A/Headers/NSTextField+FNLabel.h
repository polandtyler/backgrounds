//
//  NSTextField+FNLabel.h
//  FNAppKit
//
//  Created by Florian Bürger on 8/3/12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <AppKit/AppKit.h>

@interface NSTextField (FNLabel)

- (NSTextField *)initLabelWithFrame:(NSRect)frame;

- (BOOL)usesSingleLineMode;
- (void)setUsesSingleLineMode:(BOOL)usesSingleLineMode;
- (NSLineBreakMode)lineBreakMode;
- (void)setLineBreakMode:(NSLineBreakMode)lineBreakMode;

@end
