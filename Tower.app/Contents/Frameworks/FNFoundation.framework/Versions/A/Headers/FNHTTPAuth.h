//
//  FNHTTPAuth.h
//  FNFoundation
//
//  Created by Alexander Rinaß on 13.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol FNHTTPAuth <NSObject>
@property (nonatomic, strong, readonly) NSString *username;
@property (nonatomic, strong, readonly) NSString *password;
@end
