//
//  FNLogging.h
//  Tower
//
//  Created by Alexander Rinass on 08.09.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DDLog.h"

/*
 #pragma clang diagnostic push
 #pragma clang diagnostic ignored "-Wmultichar"
 
 (...)
 
 #pragma clang diagnostic pop
 
 This should work, but it will disable all(!!) unsused warnings...
 Marking a header files as a system Header will ignore all warnings for that file
 More info: http://clang.llvm.org/docs/UsersManual.html#diagnostics
*/
#pragma
#pragma clang system_header

#define FNFileLoggingRollingFrequency           60 * 60 * 24 // 24 hours
#define FNFileLoggingMaximumNumberOfLogFiles    7

extern int ddLogLevel;

@interface FNLogger : NSObject

+ (instancetype)sharedLogger;

+ (void)setLogLevel:(int)logLevel;
+ (NSInteger)logLevel;

- (void)setupLogging;
- (void)activateFileLogger;
- (void)deactivateFileLogger;

@end
