//
//  NSAlert+FNModal.h
//  FNAppKit
//
//  Created by Alexander Rinass on 15/08/14.
//  Copyright (c) 2014 Fournova GmbH. All rights reserved.
//

#import <Cocoa/Cocoa.h>

#if MAC_OS_X_VERSION_MIN_REQUIRED < MAC_OS_X_VERSION_10_9

@interface NSAlert (FNModal)

- (void)_beginSheetModalForWindow:(NSWindow *)sheetWindow completionHandler:(void (^)(NSModalResponse returnCode))handler;

@end
#else
#warning Method backport no longer required
#endif
