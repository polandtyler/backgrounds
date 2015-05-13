//
//  NSManagedObjectModel+FNCoreData.h
//  FNAppKit
//
//  Created by Alexander Rinaß on 06.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <CoreData/CoreData.h>

@interface NSManagedObjectModel (FNCoreData)

+ (NSManagedObjectModel *)managedObjectModelWithName:(NSString *)modelName fromBundle:(NSBundle *)bundle;

@end
