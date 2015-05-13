//
//  FNLogging.h
//  Tower
//
//  Created by Alexander Rinass on 08.09.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#ifdef DEBUG
// assertions - thanks to m. zarra - http://www.cimgf.com/2010/05/02/my-current-prefix-pch-file/
#define AssertLog(...) [[NSAssertionHandler currentHandler] handleFailureInFunction:[NSString stringWithCString:__PRETTY_FUNCTION__ encoding:NSUTF8StringEncoding] file:[NSString stringWithCString:__FILE__ encoding:NSUTF8StringEncoding] lineNumber:__LINE__ description:__VA_ARGS__]
#else
#ifndef NS_BLOCK_ASSERTIONS
#define NS_BLOCK_ASSERTIONS
#endif
#define AssertLog(...) DDLogError(__VA_ARGS__)
#endif

#define FNAssert(condition, ...) do { if (!(condition)) { AssertLog(__VA_ARGS__); }} while(0)
