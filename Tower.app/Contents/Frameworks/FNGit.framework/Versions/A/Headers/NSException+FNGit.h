//
//  NSException+FNGit.h
//  FNGit
//
//  Created by Alexander Rinass on 24.10.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

extern NSString *const FNGitCommandArgumentsOverflowException;

@class FNGitCommand;
@interface NSException (FNGit)

+ (id)gitCommandArgumentsOverflowExceptionWithGitCommand:(FNGitCommand *)gitCommand userInfo:(NSDictionary *)userInfo;

@end
