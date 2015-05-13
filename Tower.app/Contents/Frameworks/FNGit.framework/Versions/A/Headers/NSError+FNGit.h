//
//  NSError+FNGit.h
//  FNGit
//
//  Created by Alexander Rinass on 26.05.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FNGitErrors.h"

@class FNGitCommand;
@interface NSError (FNGit)

+ (instancetype)gitErrorWithCode:(NSInteger)code userInfo:(NSDictionary *)userInfo;
+ (instancetype)gitErrorWithCommand:(FNGitCommand *)command userInfo:(NSDictionary *)userInfo;

@end
