//
//  FNProductController.h
//  FNLicensing
//
//  Created by Marc Beyerlin on 07.11.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FNProductControllerDelegate.h"

extern NSString *const FNProductStatusDidUpdateNotification;
extern NSString *const FNProductStatusNotificationUserInfoKey;

@class FNProductStatus;
@class FNProductConfig;
@class FNProductActivationUserInput;
@class FNBetaLicense;
@class FNTrialLicense;
@class FNProductLicense;
@interface FNProductController : NSObject
@property (nonatomic, weak) id<FNProductControllerDelegate> delegate;
@property (nonatomic) FNProductConfig *productConfig;
@property (nonatomic, readonly) FNProductStatus *productStatus;
@property (nonatomic, readonly) FNBetaLicense *beta;
@property (nonatomic, readonly) FNTrialLicense *trial;
@property (nonatomic, readonly) FNProductLicense *license;

+ (instancetype)sharedController;

- (BOOL)hasValidProductStatus;
- (void)reloadStatus;

- (void)registerBetaWithCompletionHandler:(void (^)(NSError *))completionHandler;
- (void)registerTrialWithCompletionHandler:(void (^)(NSError *))completionHandler;
- (void)resetTrialEmail:(NSString *)email withCompletionHandler:(void (^)(NSError *))completionHandler;
- (void)activateLicenseWithInfo:(FNProductActivationUserInput *)info withCompletionHandler:(void (^)(NSError *))completionHandler;
- (void)deactivateLicense:(FNProductLicense *)license withCompletionHandler:(void (^)(NSError *))completionHandler;
- (BOOL)deleteTrialLicense:(NSError * __autoreleasing *)error;

- (void)cancel;

@end
