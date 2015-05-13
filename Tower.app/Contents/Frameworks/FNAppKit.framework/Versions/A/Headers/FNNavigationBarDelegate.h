//
//  FNNavigationBarDelegate.h
//  FNAppKit
//
//  Created by Alexander Rinass on 12.06.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@class FNNavigationBar;
@class FNNavigationItem;
@protocol FNNavigationBarDelegate <NSObject>
@optional

- (BOOL)navigationBar:(FNNavigationBar *)navigationBar shouldPushItem:(FNNavigationItem *)item;
- (void)navigationBar:(FNNavigationBar *)navigationBar didPushItem:(FNNavigationItem *)item;

- (BOOL)navigationBar:(FNNavigationBar *)navigationBar shouldPopItem:(FNNavigationItem *)item;
- (void)navigationBar:(FNNavigationBar *)navigationBar didPopItem:(FNNavigationItem *)item;

@end
