//
//  FNWindowControllerManager.h
//  Tower
//
//  Created by Tobias Günther on 30.03.12.
//  Copyright (c) 2012 fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface FNWindowControllerManager : NSObject
@property (nonatomic, readonly) NSArray *windowControllers;

/** @name Adding and Removing Window Controllers */

/*
 Adds the window controller to the array of managed controllers.
 */
- (void)addWindowController:(NSWindowController *)windowController;

/*
 Removes the window controller to the array of managed controllers.
 */
- (void)removeWindowController:(NSWindowController *)windowController;

@end
