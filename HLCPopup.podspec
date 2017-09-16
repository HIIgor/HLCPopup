Pod::Spec.new do |s|
  s.name         = "HLCPopup"
  s.version      = "0.0.2"
  s.summary      = "HLCPopup is a simple and flexible iOS class for presenting any custom view as a popup"
  s.homepage     = "https://github.com/HIIgor/HLCPopup"
  s.author       = {"HIIgor" => "http://HIIgor.com"}
  s.source_files = 'HLCPopup', 'HLCPopup/*.{h,m}'
  s.source       = {:git => 'https://github.com/HIIgor/HLCPopup.git', :tag => s.version.to_s}
  s.frameworks   = 'UIKit'
  s.requires_arc = true
  s.platform     = :ios, '7.0'
  s.license      = {
    :type => 'MIT',
    :file => 'LICENSE'
  }

end