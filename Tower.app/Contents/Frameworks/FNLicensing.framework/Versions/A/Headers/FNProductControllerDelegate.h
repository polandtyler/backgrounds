//
//  FNProductControllerDelegate.h
//  FNLicensing
//
//  Created by Marc Beyerlin on 12.11.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@class FNProductController;
@class FNProductStatus;
@protocol FNProductControllerDelegate <NSObject>
@optional

- (void)productController:(FNProductController *)controller didReloadProductStatus:(FNProductStatus *)productStatus;
- (void)productController:(FNProductController *)controller didFailToLoadProductStatusWithError:(NSError *)error;

- (void)productController:(FNProductController *)controller didFailToRegisterBetaWithError:(NSError *)error;
- (void)productController:(FNProductController *)controller didFailToRegisterTrialWithError:(NSError *)error;
- (void)productController:(FNProductController *)controller didFailToActivateLicenseWithError:(NSError *)error;
- (void)productController:(FNProductController *)controller didFailToDeactivateLicenseWithError:(NSError *)error;
- (void)productController:(FNProductController *)controller didFailToExpandTrialWithError:(NSError *)error;
- (void)productController:(FNProductController *)controller didFailToQueueTrialWithError:(NSError *)error;

@end
