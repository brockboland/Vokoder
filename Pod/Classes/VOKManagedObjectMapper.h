//
//  VOKManagedObjectMapper.h
//  Vokoder
//
//  Copyright © 2015 Vokal.
//

#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>

#import "VOKCoreDataCollectionTypes.h"
#import "VOKNullabilityFeatures.h"

#import "VOKManagedObjectMap.h"

NS_ASSUME_NONNULL_BEGIN

/// An completion block to run after importing each foreign dictionary.
typedef void(^VOKPostImportBlock)(VOKStringToObjectDictionary *inputDict, VOKManagedObjectSubclass *outputObject);

/// A completion block to run after exporting a managed object to a dictionary.
typedef void(^VOKPostExportBlock)(VOKStringToObjectMutableDictionary *outputDict, VOKManagedObjectSubclass *inputObject);

@interface VOKManagedObjectMapper : NSObject

/// Used to identify and update NSManagedObjects. Like a "primary key" in databases.
@property (nonatomic, copy) NSString * __nullable uniqueComparisonKey;

/// Used internally to filter input data. Updates automatically to match the uniqueComparisonKey.
@property (nonatomic, copy) NSString * __nullable foreignUniqueComparisonKey;

/// If set to NO changes are discarded if a local object exists with the same unique comparison key. Defaults to YES.
@property (nonatomic, assign) BOOL overwriteObjectsWithServerChanges;

/// If set to YES remote null/nil values are ignored when updating. Defaults to NO.
@property (nonatomic, assign) BOOL ignoreNullValueOverwrites;

/**
 If set to YES, will not warn about incorrect class types when receiving null/nil values for optional properties.
 Defaults to NO. Note: regardless of the setting of this property, log messages are only output in DEBUG situations.
 */
@property (nonatomic, assign) BOOL ignoreOptionalNullValues;

/// An optional completion block to run after importing each foreign dictionary. Defaults to nil.
@property (nonatomic, copy) VOKPostImportBlock __nullable importCompletionBlock;

/// An optional completion block to run after exporting a managed object to a dictionary. Defaults to nil.
@property (nonatomic, copy) VOKPostExportBlock __nullable exportCompletionBlock;

/**
 Creates a new mapper.
 @param comparisonKey   An NSString to uniquely identify local entities. Can be nil to enable duplicates.
 @param mapsArray       An NSArray of VOKManagedObjectMaps to corrdinate input data and the Core Data model.
 @return                A new mapper with the given unique key and maps.
 */
+ (instancetype)mapperWithUniqueKey:(nullable NSString *)comparisonKey
                            andMaps:(VOKArrayOfManagedObjectMaps *)mapsArray;
/**
 Convenience constructor for default mapper.
 @return    A default mapper wherein the local keys and foreign keys are identical.
 */
+ (instancetype)defaultMapper;

/**
 This override of objectForKeyedSubscript returns the foreign key for a local Core Data key.
 @param key The Core Data key.
 @return The foreign keypath as a string.
 */
- (nullable id)objectForKeyedSubscript:(id)key;

@end

NS_ASSUME_NONNULL_END
