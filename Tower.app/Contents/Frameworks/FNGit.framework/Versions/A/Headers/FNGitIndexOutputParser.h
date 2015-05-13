//
//  FNGitIndexParser.h
//  FNGit
//
//  Created by Alexander Rinass on 27.05.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#import "FNGitOutputParser.h"
#import "FNGitIndexOutputParserResultItem.h"

@interface FNGitIndexOutputParser : FNGitOutputParser
@property (nonatomic) NSArray *filePaths;
@property (nonatomic) BOOL filtersAssumeUnchangedFiles;
@property (nonatomic) BOOL filtersSubmodules;
@property (nonatomic, readonly) NSArray *indexEntries;
@end
