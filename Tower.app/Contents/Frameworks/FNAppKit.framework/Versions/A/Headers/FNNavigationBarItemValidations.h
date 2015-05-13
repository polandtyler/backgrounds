//
//  FNNavigationBarItemValidations.h
//  FNAppKit
//
//  Created by Alexander Rinass on 19.06.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol FNValidatedNavigationBarItem;
@protocol FNNavigationBarItemValidations <NSObject>

- (BOOL)validateNavigationBarItem:(id<FNValidatedNavigationBarItem>)item;

@end
