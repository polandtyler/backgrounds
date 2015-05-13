//
//  FNGitCommandDelegate.h
//  FNGit
//
//  Created by Alexander Rinass on 31.05.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <FNFoundation/FNFoundation.h>

@class FNGitCommand;
@protocol FNGitCommandDelegate <FNCommandOperationDelegate>

@optional

- (void)gitCommandDidTerminate:(FNGitCommand *)gitCommand;
- (void)gitCommandDidInterrupt:(FNGitCommand *)gitCommand;
- (void)gitCommand:(FNGitCommand *)gitCommand didReceiveStandardOutputData:(NSData *)standardOutputData;
- (void)gitCommand:(FNGitCommand *)gitCommand didReceiveStandardErrorData:(NSData *)standardErrorData;

@end
