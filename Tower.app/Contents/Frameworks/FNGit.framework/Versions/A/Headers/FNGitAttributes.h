//
//  FNGitAttributes.h
//  FNGit
//
//  Created by Alexander Rinass on 15.07.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@class FNGitRepository;
@interface FNGitAttributes : NSObject
@property (nonatomic, weak, readonly) FNGitRepository *repository;
@property (nonatomic, readonly) NSString *filePath;
@property (nonatomic, readonly) NSDictionary *attributes;

#pragma mark - Retrieving Git Attributes For File Paths

+ (NSArray *)allGitAttributesForFilePaths:(NSArray *)filePaths
                               repository:(FNGitRepository *)repository
                                    error:(NSError * __autoreleasing *)error;

+ (id)gitAttributesForFilePath:(NSString *)filePath
                    repository:(FNGitRepository *)repository
                         error:(NSError * __autoreleasing *)error;

#pragma mark - Setting or Unsetting Git Attributes For File Paths

+ (BOOL)setGitAttributeWithName:(NSString *)attributeName
             forFilePathPattern:(NSString *)filePathPattern
                     repository:(FNGitRepository *)repository
                          error:(NSError * __autoreleasing *)error;

+ (BOOL)setValue:(NSString *)aValue
forGitAttributeWithName:(NSString *)attributeName
 filePathPattern:(NSString *)filePathPattern
      repository:(FNGitRepository *)repository
           error:(NSError * __autoreleasing *)error;

+ (BOOL)unsetGitAttributeWithName:(NSString *)attributeName
               forFilePathPattern:(NSString *)filePathPattern
                       repository:(FNGitRepository *)repository
                            error:(NSError * __autoreleasing *)error;

+ (BOOL)removeGitAttributeWithName:(NSString *)attributeName
                forFilePathPattern:(NSString *)filePathPattern
                        repository:(FNGitRepository *)repository
                             error:(NSError * __autoreleasing *)error;

#pragma mark - Factory Methods

+ (id)gitAttributesWithRepository:(FNGitRepository *)repository
                         filePath:(NSString *)filePath
                       attributes:(NSDictionary *)attributes;

#pragma mark - Initialization

- (id)initWithRepository:(FNGitRepository *)repository
                filePath:(NSString *)filePath
              attributes:(NSDictionary *)attributes;

#pragma mark - Accessing Values For Git Attributes

- (BOOL)isGitAttributeSetWithName:(NSString *)attributeName;
- (NSString *)valueForGitAttributeWithName:(NSString *)attributeName;

@end
