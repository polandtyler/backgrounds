//
//  FNGitSubmoduleErrorParser.h
//  FNGit
//
//  Created by Alexander Rinass on 20.01.14.
//  Copyright (c) 2014 Fournova GmbH. All rights reserved.
//

#import "FNGitOutputParser.h"
#import "FNGitSubmoduleOutputParserResultItem.h"

@interface FNGitSubmoduleErrorOutputParser : FNGitOutputParser

- (NSArray *)result;

@end
