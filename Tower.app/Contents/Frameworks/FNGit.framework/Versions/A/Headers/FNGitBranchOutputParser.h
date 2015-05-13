//
//  FNGitBranchParser.h
//  FNGit
//
//  Created by Alexander Rinass on 16.06.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#import "FNGitOutputParser.h"
#import "FNGitBranchOutputParserResultItem.h"

@interface FNGitBranchOutputParser : FNGitOutputParser
@property (nonatomic, readonly) NSArray *branches;
@end
