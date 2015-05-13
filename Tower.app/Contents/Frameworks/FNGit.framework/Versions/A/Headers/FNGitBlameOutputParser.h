//
//  FNGitBlameOutputParser.h
//  FNGit
//
//  Created by Alexander Rinass on 22.06.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#import "FNGitOutputParser.h"
#import "FNGitBlameOutputParserResultItem.h"

@interface FNGitBlameOutputParser : FNGitOutputParser
@property (nonatomic, readonly) NSArray *annotatedLines;
@end
