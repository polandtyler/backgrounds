//
//  GitHubAPIClient.h
//  GitHubAPI
//
//  Created by Alexander Rinass on 19.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@class GitHubAuth;
@class GitHubAccount;
@class GitHubPublicKey;
@class GitHubRepository;
@interface GitHubAPIClient : NSObject
@property (nonatomic, strong) GitHubAuth *auth;
@property (nonatomic, strong) NSOperationQueue *operationQueue;

#pragma mark - Factory Methods

+ (id)clientWithAuth:(GitHubAuth *)auth;

#pragma mark - Initialization

- (id)initWithAuth:(GitHubAuth *)auth;

#pragma mark - Handle 2FA

- (BOOL)requestOTPCodeWithNote:(NSString *)note scopes:(NSArray *)scopes error:(NSError * __autoreleasing *)error;
- (NSString *)fetchAuthenticationToken:(NSString *)OTPCode note:(NSString *)note scopes:(NSArray *)scopes error:(NSError * __autoreleasing *)error;

#pragma mark - Fetching Accounts Synchronously

- (NSArray *)fetchAllUsersWithKeyword:(NSString *)keyword error:(NSError * __autoreleasing *)error;
- (GitHubAccount *)fetchCurrentUser:(NSError * __autoreleasing *)error;
- (GitHubAccount *)fetchUserWithName:(NSString *)username error:(NSError * __autoreleasing *)error;

- (NSArray *)fetchAllOrganizationRepositoriesWithName:(NSString *)organizationName error:(NSError * __autoreleasing *)error;
- (NSArray *)fetchAllOrganizationsForCurrentUser:(NSError * __autoreleasing *)error;
- (NSArray *)fetchAllOrganizationsForUserWithName:(NSString *)username error:(NSError * __autoreleasing *)error;
- (GitHubAccount *)fetchOrganizationWithName:(NSString *)organizationName error:(NSError * __autoreleasing *)error;
- (GitHubRepository *)fetchRepositoryForCurrentUserWithFullRepositoryName:(NSString *)fullRepositoryName error:(NSError * __autoreleasing *)error;

#pragma mark - Fetching Accounts Asynchronously

- (void)fetchAllUsersWithKeyword:(NSString *)keyword errorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(NSArray *users))completionHandler queue:(dispatch_queue_t)queue;
- (void)fetchCurrentUserWithErrorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(GitHubAccount *user))completionHandler queue:(dispatch_queue_t)queue;
- (void)fetchUserWithName:(NSString *)username errorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(GitHubAccount *user))completionHandler queue:(dispatch_queue_t)queue;

- (void)fetchAllOrganizationRepositoriesWithName:(NSString *)organizationName errorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(NSArray *repositories))completionHandler queue:(dispatch_queue_t)queue;
- (void)fetchAllOrganizationsForCurrentUserWithErrorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(NSArray *organizations))completionHandler queue:(dispatch_queue_t)queue;
- (void)fetchAllOrganizationsForUserWithName:(NSString *)username errorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(NSArray *organizations))completionHandler queue:(dispatch_queue_t)queue;
- (void)fetchOrganizationWithName:(NSString *)organizationName errorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(GitHubAccount *organization))completionHandler queue:(dispatch_queue_t)queue;

#pragma mark - Managing Accounts Synchronously

- (GitHubAccount *)updateUser:(GitHubAccount *)user error:(NSError * __autoreleasing *)error;
- (GitHubAccount *)updateOrganization:(GitHubAccount *)organization error:(NSError * __autoreleasing *)error;

#pragma mark - Managing Accounts Asynchronously

- (void)updateUser:(GitHubAccount *)user withErrorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(GitHubAccount *user))completionHandler queue:(dispatch_queue_t)queue;
- (void)updateOrganization:(GitHubAccount *)organization withErrorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(GitHubAccount *organization))completionHandler queue:(dispatch_queue_t)queue;

#pragma mark - Fetching Public Keys Synchronously

- (NSArray *)fetchAllPublicKeysForCurrentUser:(NSError * __autoreleasing *)error;
- (GitHubPublicKey *)fetchPublicKeyWithID:(NSInteger)publicKeyID error:(NSError * __autoreleasing *)error;

#pragma mark - Fetching Public Keys Asynchronously

- (void)fetchAllPublicKeysForCurrentUserWithErrorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(NSArray *publicKeys))completionHandler queue:(dispatch_queue_t)queue;
- (void)fetchPublicKeyWithID:(NSInteger)publicKeyID errorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(GitHubPublicKey *publicKey))completionHandler queue:(dispatch_queue_t)queue;

#pragma mark - Managing Public Keys Synchronously

- (GitHubPublicKey *)createPublicKey:(GitHubPublicKey *)publicKey error:(NSError * __autoreleasing *)error;
- (GitHubPublicKey *)updatePublicKey:(GitHubPublicKey *)publicKey error:(NSError * __autoreleasing *)error;
- (BOOL)deletePublicKeyWithID:(NSInteger)publicKeyID error:(NSError * __autoreleasing *)error;

#pragma mark - Managing Public Keys Asynchronously

- (void)createPublicKey:(GitHubPublicKey *)publicKey withErrorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(GitHubPublicKey *publicKey))completionHandler queue:(dispatch_queue_t)queue;
- (void)updatePublicKey:(GitHubPublicKey *)publicKey withErrorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(GitHubPublicKey *publicKey))completionHandler queue:(dispatch_queue_t)queue;
- (void)deletePublicKeyWithID:(NSInteger)publicKeyID errorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(void))completionHandler queue:(dispatch_queue_t)queue;

#pragma mark - Fetching Repositories Synchronously

- (NSArray *)fetchAllRepositoriesForCurrentUser:(NSError * __autoreleasing *)error;
- (NSArray *)fetchAllRepositoriesUserWithName:(NSString *)username error:(NSError * __autoreleasing *)error;
- (GitHubRepository *)fetchRepositoryForCurrentUserWithRepositoryName:(NSString *)repositoryName error:(NSError * __autoreleasing *)error;
- (GitHubRepository *)fetchRepositoryForUserWithUsername:(NSString *)username repositoryName:(NSString *)repositoryName error:(NSError * __autoreleasing *)error;

#pragma mark - Fetching Repositories Asynchronously

- (void)fetchAllRepositoriesForCurrentUserWithErrorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(NSArray *repositories))completionHandler queue:(dispatch_queue_t)queue;
- (void)fetchAllRepositoriesUserWithName:(NSString *)username errorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(NSArray *repositories))completionHandler queue:(dispatch_queue_t)queue;
- (void)fetchRepositoryForCurrentUserWithRepositoryName:(NSString *)repositoryName errorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(GitHubRepository *repository))completionHandler queue:(dispatch_queue_t)queue;
- (void)fetchRepositoryForUserWithUsername:(NSString *)username repositoryName:(NSString *)repositoryName errorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(GitHubRepository *repository))completionHandler queue:(dispatch_queue_t)queue;

#pragma mark - Managing Repositories Synchronously

- (GitHubRepository *)createRepository:(GitHubRepository *)repository error:(NSError * __autoreleasing *)error;
- (GitHubRepository *)createRepository:(GitHubRepository *)repository inOrganizationWithOrganizationName:(NSString *)organizationName error:(NSError * __autoreleasing *)error;
- (GitHubRepository *)updateRepository:(GitHubRepository *)repository error:(NSError * __autoreleasing *)error;
- (BOOL)deleteRepositoryForCurrentUserWithRepositoryName:(NSString *)repositoryName error:(NSError * __autoreleasing *)error;
- (BOOL)deleteRepositoryForOrganizationWithOrganizationName:(NSString *)organizationName repositoryName:(NSString *)repositoryName error:(NSError * __autoreleasing *)error;

#pragma mark - Managing Repositories Asynchronously

- (void)createRepository:(GitHubRepository *)repository withErrorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(GitHubRepository *repository))completionHandler queue:(dispatch_queue_t)queue;
- (void)createRepository:(GitHubRepository *)repository inOrganizationWithOrganizationName:(NSString *)organizationName errorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(GitHubRepository *repository))completionHandler queue:(dispatch_queue_t)queue;
- (void)updateRepository:(GitHubRepository *)repository withErrorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(GitHubRepository *repository))completionHandler queue:(dispatch_queue_t)queue;
- (void)deleteRepositoryForCurrentUserWithRepositoryName:(NSString *)repositoryName errorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(void))completionHandler queue:(dispatch_queue_t)queue;
- (void)deleteRepositoryForOrganizationWithOrganizationName:(NSString *)organizationName repositoryName:(NSString *)repositoryName errorHandler:(void (^)(NSError *error))errorHandler completionHandler:(void (^)(void))completionHandler queue:(dispatch_queue_t)queue;

@end
