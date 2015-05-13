//
//  FNGitTreeParser.h
//  FNGit
//
//  Created by Alexander Rinass on 04.07.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#import "FNGitOutputParser.h"
#import "FNGitTreeOutputParserResultItem.h"

@interface FNGitTreeOutputParser : FNGitOutputParser
@property (nonatomic, readonly) NSArray *treeEntries;
@end
