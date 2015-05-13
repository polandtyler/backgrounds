//
//  FNGitStatusParser.h
//  FNGit
//
//  Created by Alexander Rinass on 17.06.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#import "FNGitOutputParser.h"
#import "FNGitStatusOutputParserResultItem.h"

@interface FNGitStatusOutputParser : FNGitOutputParser
@property (nonatomic, readonly) NSArray *changedFiles;
@end
