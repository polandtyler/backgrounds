//
//  FNFoundationDefines.h
//  FNFoundation
//
//  Created by Florian Bürger on 7/2/12.
//  Copyright (c) 2012 fournova GmbH. All rights reserved.
//

#define FNNotImplementedYet() [NSException raise:@"FNNotImplementedException" format:@"Not implemented yet."];
#define FNMainThreadAssert() NSAssert([NSThread isMainThread], @"Method is expected to be performed on main thread.");
#define FNAbstractMethodAssert(methodName) NSAssert(0, @"Abstract method '%@' needs to be overridden by subclasses.", methodName);
