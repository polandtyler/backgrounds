//
//  BeanstalkAPIClient.h
//  BeanstalkAPI
//
//  Created by Alexander Rinaß on 13.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@class BeanstalkAuth;
@class BeanstalkPlan;
@class BeanstalkAccount;
@class BeanstalkUser;
@class BeanstalkPublicKey;
@class BeanstalkRepository;
@interface BeanstalkAPIClient : NSObject
@property (nonatomic, strong) BeanstalkAuth *auth;
@property (nonatomic, strong) NSOperationQueue *operationQueue;

#pragma mark - Factory Methods

+ (id)clientWithAuth:(BeanstalkAuth *)auth;

#pragma mark - Initialization

- (id)initWithAuth:(BeanstalkAuth *)auth;

#pragma mark - Fetching Accounts Synchronously

- (BeanstalkAccount *)fetchAccount:(NSError * __autoreleasing *)error;

#pragma mark - Fetching Accounts Asynchronously

- (void)fetchAccountWithErrorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(BeanstalkAccount *account))completionHandler queue:(dispatch_queue_t)queue;

#pragma mark - Managing Accounts Synchronously

- (BeanstalkAccount *)updateAccount:(BeanstalkAccount *)account error:(NSError * __autoreleasing *)error;

#pragma mark - Managing Accounts Asynchronously

- (void)updateAccount:(BeanstalkAccount *)account withErrorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(BeanstalkAccount *account))completionHandler queue:(dispatch_queue_t)queue;

#pragma mark - Fetching Plans Synchronously

- (NSArray *)fetchAllPlans:(NSError * __autoreleasing *)error;
- (BeanstalkPlan *)fetchPlanWithID:(NSInteger)planID error:(NSError * __autoreleasing *)error;

#pragma mark - Fetching Users Asynchronously

- (void)fetchAllPlansWithErrorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(NSArray *users))completionHandler queue:(dispatch_queue_t)queue;
- (void)fetchPlanWithID:(NSInteger)planID errorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(BeanstalkPlan *plan))completionHandler queue:(dispatch_queue_t)queue;

#pragma mark - Fetching Users Synchronously

- (NSArray *)fetchAllUsers:(NSError * __autoreleasing *)error;
- (BeanstalkUser *)fetchCurrentUser:(NSError * __autoreleasing *)error;
- (BeanstalkUser *)fetchUserWithID:(NSInteger)userID error:(NSError * __autoreleasing *)error;

#pragma mark - Fetching Users Asynchronously

- (void)fetchAllUsersWithErrorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(NSArray *users))completionHandler queue:(dispatch_queue_t)queue;
- (void)fetchCurrentUserWithErrorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(BeanstalkUser *user))completionHandler queue:(dispatch_queue_t)queue;
- (void)fetchUserWithID:(NSInteger)userID errorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(BeanstalkUser *user))completionHandler queue:(dispatch_queue_t)queue;

#pragma mark - Managing Users Synchronously

- (BeanstalkUser *)createUser:(BeanstalkUser *)user error:(NSError * __autoreleasing *)error;
- (BeanstalkUser *)updateUser:(BeanstalkUser *)user error:(NSError * __autoreleasing *)error;
- (BOOL)deleteUserWithID:(NSInteger)userID error:(NSError * __autoreleasing *)error;

#pragma mark - Managing Users Asynchronously

- (void)createUser:(BeanstalkUser *)user withErrorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(BeanstalkUser *user))completionHandler queue:(dispatch_queue_t)queue;
- (void)updateUser:(BeanstalkUser *)user withErrorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(BeanstalkUser *user))completionHandler queue:(dispatch_queue_t)queue;
- (void)deleteUserWithID:(NSInteger)userID errorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(void))completionHandler queue:(dispatch_queue_t)queue;

#pragma mark - Fetching Public Keys Synchronously

- (NSArray *)fetchAllPublicKeys:(NSError * __autoreleasing *)error;
- (NSArray *)fetchAllPublicKeysUserID:(NSInteger)userID error:(NSError * __autoreleasing *)error;
- (BeanstalkPublicKey *)fetchPublicKeyWithID:(NSInteger)userID error:(NSError * __autoreleasing *)error;

#pragma mark - Fetching Public Keys Asynchronously

- (void)fetchAllPublicKeysWithErrorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(NSArray *publicKeys))completionHandler queue:(dispatch_queue_t)queue;
- (void)fetchAllPublicKeysUserId:(NSInteger)userID withErrorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(NSArray *publicKeys))completionHandler queue:(dispatch_queue_t)queue;
- (void)fetchPublicKeyWithID:(NSInteger)publicKeyID errorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(BeanstalkPublicKey *publicKey))completionHandler queue:(dispatch_queue_t)queue;

#pragma mark - Managing Public Keys Synchronously

- (BeanstalkPublicKey *)createPublicKey:(BeanstalkPublicKey *)publicKey error:(NSError * __autoreleasing *)error;
- (BeanstalkPublicKey *)updatePublicKey:(BeanstalkPublicKey *)publicKey error:(NSError * __autoreleasing *)error;
- (BOOL)deletePublicKeyWithID:(NSInteger)publicKeyID error:(NSError * __autoreleasing *)error;

#pragma mark - Managing Public Keys Asynchronously

- (void)createPublicKey:(BeanstalkPublicKey *)publicKey withErrorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(BeanstalkPublicKey *publicKey))completionHandler queue:(dispatch_queue_t)queue;
- (void)updatePublicKey:(BeanstalkPublicKey *)publicKey withErrorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(BeanstalkPublicKey *publicKey))completionHandler queue:(dispatch_queue_t)queue;
- (void)deletePublicKeyWithID:(NSInteger)publicKeyID errorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(void))completionHandler queue:(dispatch_queue_t)queue;

#pragma mark - Fetching Repositories Synchronously

- (NSArray *)fetchAllRepositories:(NSError * __autoreleasing *)error;
- (BeanstalkRepository *)fetchRepositoryWithID:(NSInteger)repositoryID error:(NSError * __autoreleasing *)error;

#pragma mark - Fetching Repositories Asynchronously

- (void)fetchAllRepositoriesWithErrorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(NSArray *repositories))completionHandler queue:(dispatch_queue_t)queue;
- (void)fetchRepositoryWithID:(NSInteger)repositoryID errorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(BeanstalkRepository *repository))completionHandler queue:(dispatch_queue_t)queue;

#pragma mark - Managing Repositories Synchronously

- (BeanstalkRepository *)createRepository:(BeanstalkRepository *)repository error:(NSError * __autoreleasing *)error;
- (BeanstalkRepository *)updateRepository:(BeanstalkRepository *)repository error:(NSError * __autoreleasing *)error;

#pragma mark - Managing Repositories Asynchronously

- (void)createRepository:(BeanstalkRepository *)repository withErrorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(BeanstalkRepository *repository))completionHandler queue:(dispatch_queue_t)queue;
- (void)updateRepository:(BeanstalkRepository *)repository withErrorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(BeanstalkRepository *repository))completionHandler queue:(dispatch_queue_t)queue;

@end
