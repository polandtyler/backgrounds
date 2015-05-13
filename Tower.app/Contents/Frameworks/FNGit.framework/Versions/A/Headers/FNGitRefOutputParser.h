//
//  FNGitRefParser.h
//  FNGit
//
//  Created by Alexander Rinass on 20.06.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#import "FNGitOutputParser.h"
#import "FNGitRefOutputParserResultItem.h"

@interface FNGitRefOutputParser : FNGitOutputParser
@property (nonatomic, readonly) NSArray *refs;
@end
