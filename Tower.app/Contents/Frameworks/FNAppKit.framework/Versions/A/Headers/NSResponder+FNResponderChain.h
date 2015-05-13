//
//  NSResponder+FNResponderChain.h
//  FNAppKit
//
//  Created by Alexander Rinass on 15.04.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface NSResponder (FNResponderChain)

- (NSArray *)responderChain;
- (NSArray *)responderChainDescription;

@end
