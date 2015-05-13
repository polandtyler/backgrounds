//
//  FNPathSelectionButton.h
//  FNAppKit
//
//  Created by Florian Bürger on 09.11.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@class FNPathSelectionButton;
@protocol FNPathSelectionDelegate <NSObject>
@required
- (void)pathSelectionButton:(FNPathSelectionButton *)button didSelectPath:(NSURL *)path;
@end

@protocol FNPathSelectionDatasource <NSObject>
@optional
- (NSURL *)startURLForPathSelectionButton:(FNPathSelectionButton *)button;
@end

@interface FNPathSelectionButton : NSPopUpButton

@property (nonatomic) BOOL canChooseDirectories; // default YES
@property (nonatomic) BOOL canChooseFiles; // default NO
@property (nonatomic) BOOL canCreateDirectories; // default NO
@property (nonatomic) BOOL allowsMultipleSelection; // default NO

@property (nonatomic, weak) IBOutlet id<FNPathSelectionDelegate> delegate;
@property (nonatomic, weak) IBOutlet id<FNPathSelectionDatasource> datasource;

- (void)showOpenPanel:(id)sender;

@end
