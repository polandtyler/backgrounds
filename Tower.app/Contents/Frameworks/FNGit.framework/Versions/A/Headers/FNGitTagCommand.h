//
//  FNGitTagCommand.h
//  FNGit
//
//  Created by Alexander Rinass on 30.07.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "FNGitCommand.h"

@interface FNGitTagCommand : FNGitCommand
@property (nonatomic) NSArray *refNames;
@property (nonatomic) NSString *revision;
@property (nonatomic) NSString *message;
@property (nonatomic) BOOL deletesTag;

#pragma mark - Factory Methods

+ (id)gitCreateTagCommandWithRepository:(FNGitRepository *)repository refName:(NSString *)refName revision:(NSString *)revision message:(NSString *)message;
+ (id)gitDeleteTagCommandWithRepository:(FNGitRepository *)repository refNames:(NSArray *)refNames;

@end
