//
//  BitbucketAPIClient.h
//  BitbucketAPI
//
//  Created by Patrick Dinger on 07.02.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@class BitbucketAuth;
@class BitbucketRepository;
@class BitbucketPublicKey;
@class BitbucketUser;
@class BitbucketUserEmail;

@interface BitbucketAPIClient : NSObject

@property (nonatomic, strong) BitbucketAuth *auth;
@property (nonatomic, strong) NSOperationQueue *operationQueue;


/** @name Creating BitbucketAPIClient */

+ (id)clientWithAuth:(BitbucketAuth *)auth;
- (id)initWithAuth:(BitbucketAuth *)auth;
#pragma mark - Manage Repositories

/** @name Manage Repositories Synchronously */
- (NSArray *)fetchAllRepositoriesForAccount:(NSString *)account error:(NSError * __autoreleasing *)error;
- (NSArray *)fetchAllRepositoriesOfCurrentUser:(NSError * __autoreleasing *)error;

- (BitbucketRepository *)fetchRepositoryForAccount:(NSString *)account slug:(NSString *)slug error:(__autoreleasing NSError **)error;
- (BitbucketRepository *)createRepository:(BitbucketRepository *)repository error:(NSError * __autoreleasing *)error;
- (BitbucketRepository *)updateRepository:(BitbucketRepository *)repository error:(NSError * __autoreleasing *)error;
- (BOOL)deleteRepository:(BitbucketRepository *)repository error:(NSError * __autoreleasing *)error;

/** @name Manage Repositories Asynchronously */
- (void)fetchAllRepositoriesOfAccount:(NSString *)account errorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(NSArray *repositories))completionHandler queue:(dispatch_queue_t)queue;
- (void)fetchAllRepositoriesOfCurrentUserWithErrorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(NSArray *repositories))completionHandler queue:(dispatch_queue_t)queue;
- (void)fetchRepositoryWithSlug:(NSString *)slug account:(NSString *)account errorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(BitbucketRepository *repository))completionHandler queue:(dispatch_queue_t)queue;
- (void)createRepository:(BitbucketRepository *)repository withErrorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(BitbucketRepository *repository))completionHandler queue:(dispatch_queue_t)queue;
- (void)updateRepository:(BitbucketRepository *)repository withErrorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(BitbucketRepository *repository))completionHandler queue:(dispatch_queue_t)queue;
- (void)deleteRepository:(BitbucketRepository *)repository withErrorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(void))completionHandler queue:(dispatch_queue_t)queue;
#pragma mark - Manage Public Keys

/** @name Manage Public Keys Synchronously */
- (BitbucketPublicKey *)createPublicKey:(BitbucketPublicKey *)publicKey error:(NSError * __autoreleasing *)error;
- (BitbucketPublicKey *)updatePublicKey:(BitbucketPublicKey *)publicKey error:(NSError * __autoreleasing *)error;
- (BOOL)deletePublicKeyWithID:(NSInteger)publicKeyID error:(NSError * __autoreleasing *)error;
- (NSArray *)fetchAllPublicKeys:(NSError * __autoreleasing *)error;

/** @name Manage Public Keys Asynchronously */
- (void)createPublicKey:(BitbucketPublicKey *)publicKey withErrorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(BitbucketPublicKey *publicKey))completionHandler queue:(dispatch_queue_t)queue;
- (void)updatePublicKey:(BitbucketPublicKey *)publicKey withErrorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(BitbucketPublicKey *publicKey))completionHandler queue:(dispatch_queue_t)queue;
- (void)deletePublicKeyWithID:(NSInteger)publicKeyID errorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(void))completionHandler queue:(dispatch_queue_t)queue;
- (void)fetchAllPublicKeysWithErrorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(NSArray *publicKeys))completionHandler queue:(dispatch_queue_t)queue;
#pragma mark - Manage Users

/** @name Manage Users Synchronously */
- (BitbucketUser *)fetchCurrentUser:(NSError * __autoreleasing *)error;
- (BitbucketUser *)fetchUserWithUsername:(NSString *)username error:(NSError * __autoreleasing *)error;
- (BitbucketUser *)updateUser:(BitbucketUser *)user error:(NSError * __autoreleasing *)error;
- (BitbucketUser *)createUser:(BitbucketUser *)user error:(NSError * __autoreleasing *)error;


/** @name Manage Users Asynchronously */
- (void)fetchCurrentUser:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(BitbucketUser *user))completionHandler queue:(dispatch_queue_t)queue;
- (void)fetchUserWithUsername:(NSString *)username error:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(BitbucketUser *user))completionHandler queue:(dispatch_queue_t)queue;
- (void)updateUser:(BitbucketUser *)user withErrorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(BitbucketUser *user))completionHandler queue:(dispatch_queue_t)queue;
- (void)createUser:(BitbucketUser *)user withErrorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(BitbucketUser *user))completionHandler queue:(dispatch_queue_t)queue;

#pragma mark - User Email Synchron

- (BitbucketUserEmail *)fetchCurrentUserEmail:(NSError * __autoreleasing *)error;
#pragma mark - User Email Asynchron


- (void)fetchCurrentUserEmail:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(BitbucketUserEmail *userEmail))completionHandler queue:(dispatch_queue_t)queue;

@end
