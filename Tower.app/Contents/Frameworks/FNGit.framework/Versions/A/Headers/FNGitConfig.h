//
//  FNGitConfig.h
//  FNGit
//
//  Created by Alexander Rinass on 14.01.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 User Config Keys
 */
extern NSString *const FNGitUserNameConfigKey;
extern NSString *const FNGitUserEmailConfigKey;

/**
 Core Config Keys
 */
extern NSString *const FNGitCoreExcludesFileConfigKey;

/**
 HTTP Config Keys
 */
extern NSString *const FNGitHTTPProxyConfigKey;
extern NSString *const FNGitHTTPSSLVerifyConfigKey;

/**
 Status Config Keys
 */
extern NSString *const FNGitStatusShowUntrackedFilesConfigKey;

/**
 Branch Config Keys
 */
extern NSString *const FNGitBranchRemoteConfigKey;
extern NSString *const FNGitBranchMergeConfigKey;
extern NSString *const FNGitBranchMergeOptionsConfigKey;
extern NSString *const FNGitBranchRebaseConfigKey;

/**
 Remote Config Keys
 */
extern NSString *const FNGitRemoteURLConfigKey;
extern NSString *const FNGitRemotePushURLConfigKey;
extern NSString *const FNGitRemoteFetchConfigKey;
extern NSString *const FNGitRemotePushConfigKey;
extern NSString *const FNGitRemoteProxyConfigKey;
extern NSString *const FNGitRemoteTagOptConfigKey;
extern NSString *const FNGitRemoteSkipDefaultUpdateConfigKey;
extern NSString *const FNGitRemoteSkipFetchAllConfigKey;

/**
 SVN Remote Config Keys
 */
extern NSString *const FNGitSVNRemoteURLConfigKey;
extern NSString *const FNGitSVNRemoteCommitURLConfigKey;
extern NSString *const FNGitSVNRemoteFetchConfigKey;
extern NSString *const FNGitSVNRemoteBranchesConfigKey;
extern NSString *const FNGitSVNRemoteTagsConfigKey;
extern NSString *const FNGitSVNRemoteUUIDConfigKey;

/**
 Submodule Config Keys 
 */
extern NSString *const FNGitSubmoduleURLConfigKey;
extern NSString *const FNGitSubmodulePathConfigKey;
extern NSString *const FNGitSubmoduleIgnoreConfigKey;
extern NSString *const FNGitSubmoduleUpdateConfigKey;
extern NSString *const FNGitSubmoduleFetchRecurseSubmodulesConfigKey;

@class FNGitRepository;
@interface FNGitConfig : NSObject
@property (nonatomic, weak, readonly) FNGitRepository *repository;@property (nonatomic, readonly) NSString *configFile;

#pragma mark - Accessing Global Values for Git Config Keys

+ (NSString *)globalValueForConfigKey:(NSString *)configKey error:(NSError * __autoreleasing *)error;
+ (NSArray *)globalValuesForConfigKey:(NSString *)configKey error:(NSError * __autoreleasing *)error;

#pragma mark - Accessing Values for Git Config Keys for a Repository

+ (NSString *)valueForConfigKey:(NSString *)configKey repository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;
+ (NSArray *)valuesForConfigKey:(NSString *)configKey repository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;

#pragma mark - Factory Methods

/**
 Retrieves the system wide Git config file (`$(prefix)/etc/gitconfig`).
 
 Only values that are in this file are considered for reading and writing.
 */
+ (id)systemWideConfig;

/**
 Retrieves the global Git config file (`$HOME/.gitconfig`).
 
 Only values that are in this file are considered for reading and writing.
 */
+ (id)globalConfig;

/**
 Retrieves the repository's config file (`.git/config`).
 
 Only values that are in this file are considered for reading and writing.
 */
+ (id)repositoryConfigForRepository:(FNGitRepository *)repository;

/**
 Retrieves the repository's submodule config file (`.gitmodules`). 
 
 Only values that are in this file are considered for reading and writing.
 */
+ (id)submoduleConfigForRepository:(FNGitRepository *)repository;

/**
 Retrieves the repository's git-svn config file (`.git/svn/.metadata`). 
 
 Only values that are in this file are considered for reading and writing.
 */
+ (id)gitSVNConfigForRepository:(FNGitRepository *)repository;

/**
 Retrieves the config for a repository. 
 
 When reading values, the system wide and global config are also read for default values.
 When writing values, only the repository's config file is written to.
 */
+ (id)configWithRepository:(FNGitRepository *)repository;

/**
 Retrieves the config at the given path.
 */
+ (id)configWithFilePath:(NSString *)configFilePath;

#pragma mark - Initialization

- (id)initWithRepository:(FNGitRepository *)repository configFile:(NSString *)configFile;

#pragma mark - Retrieving and Setting User`s Name and Email

- (NSString *)userName;
- (BOOL)setUserName:(NSString *)name error:(NSError * __autoreleasing *)error;

- (NSString *)userEmail;
- (BOOL)setUserEmail:(NSString *)email error:(NSError * __autoreleasing *)error;

#pragma mark - Testing Config Keys and Values

/**
 Wether or not the given config key exists.
 */
- (BOOL)containsConfigKeyWithName:(NSString *)configKey;

/**
 Wether or not the given config key has multiple values.
 
 If the config key does not exist, `NO` will be returned.
 */
- (BOOL)containsMultipleValuesForConfigKey:(NSString *)configKey;

#pragma mark - Retrieving, Setting and Unsetting Values for Config Keys

/**
 Returns the value for the given config key.
 
 Note that this method will return an error if the config key has multiple values.
 
 The option `FNGitEnsureBooleanValueConfigOption` or `FNGitEnsureIntegerValueConfigOption` can be passed
 to ensure a boolean or integer value. If one of these options is given and the value cannot be interpreted
 as the ensured type, an error will be returned.
 
 If the config key has no value or does not exist, `nil` will be returned with the error object set 
 to `nil` as well. Any other errors will return `nil` and an error object containing detailed information 
 about the error.
 */
- (NSString *)valueForConfigKey:(NSString *)configKey options:(NSDictionary *)options error:(NSError * __autoreleasing *)error;

/**
 Returns the value for the given config key.
 
 Note that this method will return an error if the config key has multiple values.
 
 If the config key has no value or does not exist, `nil` will be returned with the error object set 
 to `nil` as well. Any other errors will return `nil` and an error object containing detailed information 
 about the error.
 */
- (NSString *)valueForConfigKey:(NSString *)configKey error:(NSError * __autoreleasing *)error;

/**
 Returns the value for the given config key.
 
 If the value cannot be interpreted as a boolean value, an error will be returned.
 
 Note that this method will return an error if the config key has multiple values.
 
 If the config key has no value or does not exist, `NO` will be returned with the error object set 
 to `nil` as well. Any other errors will return `NO` and an error object containing detailed information 
 about the error.
 */
- (BOOL)boolForConfigKey:(NSString *)configKey error:(NSError * __autoreleasing *)error;

/**
 Returns the value for the given config key.
 
 If the value cannot be interpreted as an integer value, an error will be returned.
 
 Note that this method will return an error if the config key has multiple values.
 
 If the config key has no value or does not exist, `NSNotFound` will be returned with the error object set 
 to `nil` as well. Any other errors will return `NSNotFound` and an error object containing detailed information 
 about the error.
 */
- (NSInteger)integerForConfigKey:(NSString *)configKey error:(NSError * __autoreleasing *)error;

/**
 Returns the first value for the given config key in case it contains multiple values.
 
 If the config key only has one value, this one will be returned.
 
 If the config key has no value or does not exist, `nil` will be returned with the error object set 
 to `nil` as well. Any other errors will return `nil` and an error object containing detailed information 
 about the error.
 */
- (NSString *)firstValueForConfigKey:(NSString *)configKey error:(NSError * __autoreleasing *)error;

/**
 Returns the last value for the given config key in case it contains multiple values.
 
 If the config key only has one value, this one will be returned.
 
 If the config key has no value or does not exist, `nil` will be returned with the error object set 
 to `nil` as well. Any other errors will return `nil` and an error object containing detailed information 
 about the error.
 */
- (NSString *)lastValueForConfigKey:(NSString *)configKey error:(NSError * __autoreleasing *)error;

/**
 Returns all values for the given config key.
 
 If the config key only has one value, an array with one entry will be returned.
 
 If the config key has no value or does not exist, `nil` will be returned with the error object set 
 to `nil` as well. Any other errors will return `nil` and an error object containing detailed information 
 about the error.
 */
- (NSArray *)valuesForConfigKey:(NSString *)configKey error:(NSError * __autoreleasing *)error;

/**
 Returns all values that match the given config key regex pattern (as defined in `man git-config`).
 
 If the config key only has one value, an array with one entry containing this value will be returned.
 
 If the config key has no value or does not exist, `nil` will be returned with the error object set 
 to `nil` as well. Any other errors will return `nil` and an error object containing detailed information 
 about the error.
 */
- (NSDictionary *)valuesForConfigKeyByRegularExpression:(NSString *)configKeyRegularExpression error:(NSError * __autoreleasing *)error;

/**
 Sets the given value for the given config key. 
 
 If value is nil, the config key will be unset. If the key has multiple values, they will be overwritten
 with the one given value.
 
 The option `FNGitEnsureBooleanValueConfigOption` or `FNGitEnsureIntegerValueConfigOption` can be passed
 to ensure a boolean or integer value is written. If one of these options is given and the value cannot 
 be interpreted as the ensured type, an error will be returned.
 
 Any errors will return `NO` and an error object containing detailed information about the error. 
 */
- (BOOL)setValue:(NSString *)value forConfigKey:(NSString *)configKey options:(NSDictionary *)options error:(NSError * __autoreleasing *)error;

/**
 Replaces the given value for the given config key with the given new value.
 
 If value is nil, the matching value for the config key will be unset. If no value matches, `NO` will be 
 returned with error set to `nil`.
 
 Any errors will return `NO` and an error object containing detailed information about the error. 
 */
- (BOOL)replaceValue:(NSString *)value withNewValue:(NSString *)newValue forConfigKey:(NSString *)configKey error:(NSError * __autoreleasing *)error;

/**
 Sets the given value for the given config key.
 
 If value is nil, the config key will be unset. If the key has multiple values, they will be overwritten
 with the one given value.
 
 Any errors will return `NO` and an error object containing detailed information about the error. 
 */
- (BOOL)setValue:(NSString *)value forConfigKey:(NSString *)configKey error:(NSError * __autoreleasing *)error;

/**
 Sets the given boolean value for the given config key.
 
 Any errors will return `NO` and an error object containing detailed information about the error.
 */
- (BOOL)setBool:(BOOL)value forConfigKey:(NSString *)configKey error:(NSError * __autoreleasing *)error;

/**
 Sets the given integer value for the given config key.
 
 Any errors will return `NO` and an error object containing detailed information about the error. 
 */
- (BOOL)setInteger:(NSInteger)value forConfigKey:(NSString *)configKey error:(NSError * __autoreleasing *)error;

/**
 Sets the given values for the given config key. Any existing values for the config key will be overwritten.
 
 Any errors will return `NO` and an error object containing detailed information about the error. 
 */
- (BOOL)setValues:(NSArray *)values forConfigKey:(NSString *)configKey error:(NSError * __autoreleasing *)error;

/**
 Adds the given value to the given config key. If the config key does not exist, th value will be set as the
 config key's only value.
 
 Any errors will return `NO` and an error object containing detailed information about the error. 
 */
- (BOOL)addValue:(NSString *)value forConfigKey:(NSString *)configKey error:(NSError * __autoreleasing *)error;

/**
 Adds the given values to the given config key.
 
 Any errors will return `NO` and an error object containing detailed information about the error. 
 */
- (BOOL)addValues:(NSArray *)values forConfigKey:(NSString *)configKey error:(NSError * __autoreleasing *)error;

/**
 Unsets only the given value for the given config key. If the config key has multiple values, only
 values matching value will be removed.
 
 If the config key has no more values, it will be removed completely.
 
 If the value or the config key does not exist, NO is returned with error set to `nil`.
 
 Any errors will return `NO` and an error object containing detailed information about the error. 
 */
- (BOOL)unsetValue:(NSString *)value forConfigKey:(NSString *)configKey error:(NSError * __autoreleasing *)error;

/**
 Unsets the given config key with all of its values.
 
 If the config key does not exist, NO is returned with error set to `nil`.
 
 Any errors will return `NO` and an error object containing detailed information about the error. 
 */
- (BOOL)unsetConfigKey:(NSString *)configKey error:(NSError * __autoreleasing *)error;

#pragma mark - Testing Config Sections

/**
 Wether or not the given section name exists.
 */
- (BOOL)containsSectionWithName:(NSString *)sectionName;

#pragma mark - Removing or Renaming Config Sections

/**
 Removes the given config section.
 
 If the section does not exist, NO is returned with error set to `nil`.
 
 Any errors will return `NO` and an error object containing detailed information about the error. 
 */
- (BOOL)removeSection:(NSString *)sectionName error:(NSError * __autoreleasing *)error;

/**
 Renames the given config section to the new given name.
 
 If the section does not exist, NO is returned with error set to `nil`.
 
 Any errors will return `NO` and an error object containing detailed information about the error. 
 */
- (BOOL)renameSection:(NSString *)sectionName toNewSectionName:(NSString *)newSectionName error:(NSError * __autoreleasing *)error;

#pragma mark - Retrieving Dictionary Representation

- (NSDictionary *)dictionaryRepresentation;

@end
