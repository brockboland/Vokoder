Pod::Spec.new do |s|
  s.name             = "Vokoder"
  s.version          = "2.1.0"
  s.summary          = "Vokal's Core Data Manager"
  s.homepage         = "https://github.com/vokal/Vokoder"
  s.license          = { :type => "MIT", :file => "LICENSE"}
  s.author           = { "Vokal" => "hello@vokal.io" }
  s.source           = { :git => "https://github.com/vokal/Vokoder.git", :tag => s.version.to_s }

  s.platform     = :ios, '7.0'
  s.requires_arc = true

  s.default_subspecs = 'Core', 'DataSources'

  s.subspec 'Core' do |ss|
    ss.source_files = [
      'Pod/Classes/*.{h,m}',
      'Pod/Classes/Internal',
    ]
    ss.framework    = "CoreData"
    ss.dependency 'ILGDynamicObjC/ILGClasses', '~> 0.1.1'
  end

  s.subspec 'DataSources' do |ss|
    ss.dependency 'Vokoder/Core'

    ss.default_subspecs = 'FetchedResults', 'PagingFetchedResults', 'Collection'

    ss.subspec 'FetchedResults' do |sss|
      sss.source_files = 'Pod/Classes/Optional Data Sources/VOKFetchedResultsDataSource.{h,m}'
    end

    ss.subspec 'PagingFetchedResults' do |sss|
      sss.source_files = [
        'Pod/Classes/Optional Data Sources/VOKPagingFetchedResultsDataSource.{h,m}',
        'Pod/Classes/Optional Data Sources/VOKDefaultPagingAccessory.{h,m}',
      ]
      sss.dependency 'Vokoder/DataSources/FetchedResults'
    end

    ss.subspec 'Collection' do |sss|
      sss.source_files = 'Pod/Classes/Optional Data Sources/VOKCollectionDataSource.{h,m}'
      sss.dependency 'Vokoder/DataSources/FetchedResults'
    end
  end

  s.subspec 'Swift' do |sw|
    sw.dependency 'Vokoder/DataSources'
    sw.source_files = [
      'Pod/Classes/Swift/*.swift'
    ]
  end
end
