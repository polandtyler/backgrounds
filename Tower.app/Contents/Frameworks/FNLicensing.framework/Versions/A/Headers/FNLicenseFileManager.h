//
//  FNLicenseFileManager.h
//  FNLicensing
//
//  Created by Marc Beyerlin on 05.11.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@class FNProductConfig;
@class FNBetaLicense;
@class FNTrialLicense;
@class FNProductLicense;
@interface FNLicenseFileManager : NSObject
@property (nonatomic, readonly) FNProductConfig *productConfig;
@property (nonatomic, readonly) NSURL *betaLicenseFileURL;
@property (nonatomic, readonly) NSURL *trialLicenseFileURL;
@property (nonatomic, readonly) NSURL *productLicenseFileURL;
@property (nonatomic, readonly) NSURL *destinationDirectoryURL;

- (instancetype)initWithProductConfig:(FNProductConfig *)productConfig;

/** @name Reading License Files */

- (FNBetaLicense *)readBetaLicense;
- (FNTrialLicense *)readTrialLicense;
- (FNProductLicense *)readProductLicense;

/** @name Writing License Files */

- (BOOL)writeBetaLicense:(FNBetaLicense *)license error:(NSError * __autoreleasing *)error;
- (BOOL)writeTrialLicense:(FNTrialLicense *)license error:(NSError * __autoreleasing *)error;
- (BOOL)writeProductLicense:(FNProductLicense *)license error:(NSError * __autoreleasing *)error;

- (BOOL)writeBetaFileWithContent:(NSString *)content error:(NSError * __autoreleasing *)error;
- (BOOL)writeTrialFileWithContent:(NSString *)content error:(NSError * __autoreleasing *)error;
- (BOOL)writeLicenseFileWithContent:(NSString *)content error:(NSError * __autoreleasing *)error;

/** @name Deleting License Files */

- (BOOL)deleteBetaFileError:(NSError * __autoreleasing *)error;
- (BOOL)deleteLicenseFileError:(NSError * __autoreleasing *)error;
- (BOOL)deleteTrialFileError:(NSError * __autoreleasing *)error;

@end
