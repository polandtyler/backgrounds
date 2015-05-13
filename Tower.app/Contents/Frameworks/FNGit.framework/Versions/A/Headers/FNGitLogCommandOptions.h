//
//  FNGitLogCommandOptions.h
//  FNGit
//
//  Created by Alexander Rinass on 16.08.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

extern NSString *const FNGitLogOptionReverseOrder;
extern NSString *const FNGitLogOptionSortByTopoOrder;
extern NSString *const FNGitLogOptionSortByDate;
extern NSString *const FNGitLogOptionFollowRenames;
extern NSString *const FNGitLogOptionLimit;
extern NSString *const FNGitLogOptionOffset;
extern NSString *const FNGitLogOptionDecorate;
extern NSString *const FNGitLogOptionSearchPattern;
extern NSString *const FNGitLogOptionAllBranches;
extern NSString *const FNGitLogOptionAllRemoteBranches;
extern NSString *const FNGitLogOptionAllTags;
extern NSString *const FNGitLogOptionAllRefs;
extern NSString *const FNGitLogOptionSearchAuthorPattern;
extern NSString *const FNGitLogOptionSearchCommitterPattern;
extern NSString *const FNGitLogOptionFirstParent;

@interface FNGitLogCommandOptions : NSObject

@end
