//
//  FNTabbedWindowController.h
//  Tower
//
//  Created by Tobias Günther on 01.02.12.
//  Copyright (c) 2012 n/a. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "FNWindowController.h"

@interface FNTabbedWindowController : FNWindowController {
@private
    NSInteger currentlyOpenTab;
}
@property NSInteger currentlyOpenTab;
#pragma mark Opening Tabs / Showing Views
- (IBAction)showTabAction:(id)sender;
- (void)showTab:(NSInteger)tabTag;

@end



@protocol FNTabbedWindowControllerProtocol <NSObject>
- (NSString *)windowTitleForCurrentlyOpenToolbarItem:(NSToolbarItem *)toolbarItem;
- (NSView *)contentViewForTabWithTag:(NSInteger)tabTag;
@end
