//
//  FNGitSubmoduleConfigHelper.h
//  FNGit
//
//  Created by Alexander Rinass on 22.10.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FNGitSubmoduleOptions.h"

@interface FNGitSubmoduleConfigHelper : NSObject

+ (FNGitSubmoduleUpdateStrategy)updateStrategyFromConfigValue:(NSString *)value;
+ (NSString *)updateStrategyToConfigValue:(FNGitSubmoduleUpdateStrategy)updateStrategy;

+ (FNGitSubmoduleStatusIgnoreMode)statusIgnoreModeFromConfigValue:(NSString *)value;
+ (NSString *)statusIgnoreModeToConfigValue:(FNGitSubmoduleStatusIgnoreMode)statusIgnoreMode;

+ (NSString *)submoduleConfigSectionWithSubmoduleName:(NSString *)submoduleName;
+ (NSString *)submoduleConfigKeyWithSubmoduleName:(NSString *)submoduleName configKey:(NSString *)configKey;

@end
