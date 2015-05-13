//
//  FNGitAttributesOutputParser.h
//  FNGit
//
//  Created by Alexander Rinass on 25.07.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#import "FNGitOutputParser.h"
#import "FNGitAttributesOutputParserResultItem.h"

@interface FNGitAttributesOutputParser : FNGitOutputParser
@property (nonatomic, readonly) NSArray *attributes;
@end
