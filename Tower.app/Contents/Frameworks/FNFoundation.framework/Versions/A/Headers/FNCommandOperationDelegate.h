//
//  FNCommandOperationDelegate.h
//  FNFoundation
//
//  Created by Alexander Rinass on 26/03/14.
//  Copyright (c) 2014 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@class FNCommandOperation;
@protocol FNCommandOperationDelegate <NSObject>
@optional

- (void)commandDidFailToLaunch:(FNCommandOperation *)command;
- (void)commandDidTerminate:(FNCommandOperation *)command;
- (void)command:(FNCommandOperation *)command didReceiveStandardOutputData:(NSData *)standardOutputData;
- (void)command:(FNCommandOperation *)command didReceiveStandardErrorData:(NSData *)standardErrorData;

@end
