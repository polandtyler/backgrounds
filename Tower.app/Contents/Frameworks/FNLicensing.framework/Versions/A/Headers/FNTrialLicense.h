//
//  FNProductTrial.h
//  Tower
//
//  Created by Alexander Rinass on 24.08.10.
//  Copyright 2010 puremedia GmbH. All rights reserved.
//

#import "FNAbstractLicense.h"

@interface FNTrialLicense : FNAbstractLicense

+ (instancetype)licenseWithValuesFromDictionary:(NSDictionary *)values;

@end
