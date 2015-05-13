//
//  FNGitConfigCommand.h
//  FNGit
//
//  Created by Alexander Rinass on 31.07.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "FNGitCommand.h"

extern NSString *const FNGitConfigOptionConfigFilePath;
extern NSString *const FNGitConfigOptionConfigFileType;

extern NSString *const FNGitConfigOptionConfigAction;

extern NSString *const FNGitConfigOptionEnsureBooleanValue;
extern NSString *const FNGitConfigOptionEnsureIntegerValue;

extern NSString *const FNGitConfigFileTypeSystem;
extern NSString *const FNGitConfigFileTypeGlobal;

extern NSString *const FNGitConfigActionGetValue;
extern NSString *const FNGitConfigActionGetAllValues;
extern NSString *const FNGitConfigActionGetAllValuesByRegularExpression;
extern NSString *const FNGitConfigActionReplaceAllValues;
extern NSString *const FNGitConfigActionAddValue;
extern NSString *const FNGitConfigActionUnsetValue;
extern NSString *const FNGitConfigActionUnsetAllValues;
extern NSString *const FNGitConfigActionRenameSection;
extern NSString *const FNGitConfigActionRemoveSection;

@interface FNGitConfigCommand : FNGitCommand
@property (nonatomic) NSString *configFilePath;
@property (nonatomic) NSString *configFileType;
@property (nonatomic) NSString *configAction;
@property (nonatomic) NSString *configKey;
@property (nonatomic) NSString *configValue;
@property (nonatomic) NSString *configValueRegex;
@property (nonatomic) BOOL ensuresBooleanValue;
@property (nonatomic) BOOL ensuresIntegerValue;
@property (nonatomic, readonly) NSArray *configValues;
@property (nonatomic, readonly) NSDictionary *configOptions;

/** @name Creating Instances */

+ (id)gitConfigCommandWithRepositoryPath:(NSString *)repositoryPath options:(NSDictionary *)options;
- (id)initWithRepositoryPath:(NSString *)repositoryPath options:(NSDictionary *)options;

@end
