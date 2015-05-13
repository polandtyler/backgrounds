//
//  FNGitSubmoduleConfig.h
//  FNGit
//
//  Created by Alexander Rinass on 12.08.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FNGitDefines.h"
#import "FNGitSubmoduleOptions.h"

@class FNGitRepository;
@interface FNGitSubmoduleConfig : NSObject
@property (nonatomic, weak, readonly) FNGitRepository *repository;
@property (nonatomic, readonly) FNGitSubmoduleConfigType configType;
@property (nonatomic, readonly) NSString *path;
@property (nonatomic, readonly) NSString *name;
@property (nonatomic, readonly) NSString *URL;
@property (nonatomic, readonly) FNGitSubmoduleUpdateStrategy updateStrategy;
@property (nonatomic, readonly) FNGitSubmoduleStatusIgnoreMode statusIgnoreMode;
@property (nonatomic, readonly) NSString *branch;
@property (nonatomic, readonly) BOOL recursesSubmoduleOnFetch;

/** @name Getting Submodule Configs */

+ (NSArray *)allSubmoduleConfigsForRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;
+ (NSArray *)allLocalSubmoduleConfigsForRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;

/** @name Managing Values */

- (BOOL)setURL:(NSString *)submoduleURL error:(NSError * __autoreleasing *)error;
- (BOOL)setUpdateStrategy:(FNGitSubmoduleUpdateStrategy)updateStrategy error:(NSError * __autoreleasing *)error;
- (BOOL)setStatusIgnoreMode:(FNGitSubmoduleStatusIgnoreMode)statusIgnoreMode error:(NSError * __autoreleasing *)error;
- (BOOL)setBranch:(NSString *)branch error:(NSError * __autoreleasing *)error;
- (BOOL)setRecursesSubmoduleOnFetch:(BOOL)recursesSubmoduleOnFetch error:(NSError * __autoreleasing *)error;

- (BOOL)unsetURL:(NSError * __autoreleasing *)error;
- (BOOL)unsetUpdateStrategy:(NSError * __autoreleasing *)error;
- (BOOL)unsetStatusIgnoreMode:(NSError * __autoreleasing *)error;
- (BOOL)unsetBranch:(NSError * __autoreleasing *)error;
- (BOOL)unsetRecursesSubmoduleOnFetch:(NSError * __autoreleasing *)error;

- (BOOL)removeConfigSection:(NSError * __autoreleasing *)error;

@end
