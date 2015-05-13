//
//  FNGitFileEntry.h
//  FNGit
//
//  Created by Alexander Rinaß on 08.03.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <FNFoundation/FNFoundation.h>
#import "FNGitDefines.h"

@class FNGitRepository;
@interface FNGitFileEntry : NSObject
@property (nonatomic, weak, readonly) FNGitRepository *repository;
@property (nonatomic, readonly) NSString *filePath;
@property (nonatomic, readonly) NSString *fileName;
@property (nonatomic, readonly) NSString *objectHash;
@property (nonatomic) FNGitFileMode fileMode;
@property (nonatomic, readonly) BOOL isNoFileType;
@property (nonatomic, readonly) BOOL isRegularFileType;
@property (nonatomic, readonly) BOOL isExecutableFileType;
@property (nonatomic, readonly) BOOL isSymbolicLinkFileType;
@property (nonatomic, readonly) BOOL isSubmoduleFileType;
@property (nonatomic, readonly) BOOL isDirectoryFileType;

#pragma mark - String Representation for File Modes

+ (NSString *)stringRepresentationForFileMode:(FNGitFileMode)fileMode;

#pragma mark - File Mode From String

+ (FNGitFileMode)fileModeFromString:(NSString *)fileModeString;

#pragma mark - Factory Methods

+ (id)fileEntryWithRepository:(FNGitRepository *)repository
					 filePath:(NSString *)filePath
				   objectHash:(NSString *)objectHash
					 fileMode:(FNGitFileMode)fileMode;

#pragma mark - Initialization

- (id)initWithRepository:(FNGitRepository *)repository
				filePath:(NSString *)filePath
			  objectHash:(NSString *)objectHash
				fileMode:(FNGitFileMode)fileMode;

#pragma mark - Comparing to Another File Entry

- (BOOL)isEqualToFileEntry:(FNGitFileEntry *)object;

@end
