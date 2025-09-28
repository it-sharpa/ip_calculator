# spec file for package ip-range v.0-10
# rules v.1.0
#
# Copyright (c) 2025 'Eugene Lutin' <tylerfc@inbox.ru>
# The license for this file: Apache-2.0

Name:           ip-range
Summary:        ip calculator
URL:            https://github.com/it-sharpa/ip_calculator
License:        Apache-2.0
Provides:       ip-range
Version:        0.10
Release:        0%{?dist}
Source0:        %{SOURCE0}/
BuildArch:      x86_64
Conflicts:      ip-range-universal
Requires:       bash
Requires:       glibc >= 2.34

%description
utility, which calculating network settings usage IP-address and mask. ip-range developing on C language

%install
rm -rf /root/rpmbuild/BUILDROOT/*
rm -rf /root/rpmbuild/RPMS/*/*
mkdir -p %{buildroot}/%{_exec_prefix}/bin/ %{buildroot}/%{_datarootdir}/man/man1/
install -Dpm 0555 /root/rpmbuild/%{_exec_prefix}/bin/%{name} %{buildroot}/%{_exec_prefix}/bin/%{name}
install -Dpm 0444 /root/rpmbuild/%{_datarootdir}/man/man1/%{name}.1.gz %{buildroot}/%{_datarootdir}/man/man1/%{name}.1.gz

%files
%{_exec_prefix}/bin/%{name}
%doc %{_datarootdir}/man/man1/%{name}.1.gz

%changelog
* Mon Jun 23 2025 root - 0:0.10
- added minimum functional IP calculator
