<?php
/* $Id$ */
/*
	globals.inc
	part of pfSense (https://www.pfsense.org)
	Copyright (C) 2004-2010 Scott Ullrich

	Originally Part of m0n0wall
	Copyright (C) 2003-2004 Manuel Kasper <mk@neon1.net>.
	All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:

	1. Redistributions of source code must retain the above copyright notice,
	   this list of conditions and the following disclaimer.

	2. Redistributions in binary form must reproduce the above copyright
	   notice, this list of conditions and the following disclaimer in the
	   documentation and/or other materials provided with the distribution.

	THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
	INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
	AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
	AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
	OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
	SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
	INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
	CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
	ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
	POSSIBILITY OF SUCH DAMAGE.

	pfSense_MODULE:	utils

*/

global $g;
$g = array(
	"base_packages" => "siproxd",
	"event_address" => "unix:///var/run/check_reload_status",
	"factory_shipped_username" => "admin",
	"factory_shipped_password" => "pfsense",
	"upload_path" => "/root",
	"dhcpd_chroot_path" => "/var/dhcpd",
	"unbound_chroot_path" => "/var/unbound",
	"var_path" => "/var",
	"varrun_path" => "/var/run",
	"varetc_path" => "/var/etc",
	"vardb_path" => "/var/db",
	"varlog_path" => "/var/log",
	"etc_path" => "/etc",
	"tmp_path" => "/tmp",
	"conf_path" => "/conf",
	"ftmp_path" => "/ftmp",
	"conf_default_path" => "/conf.default",
	"cf_path" => "/cf",
	"cf_conf_path" => "/cf/conf",
	"www_path" => "/usr/local/www",
	"xml_rootobj" => "pfsense",
	"admin_group" => "admins",
	"product_name" => "pfSense",
	"product_copyright" => "Electric Sheep Fencing LLC",
	"product_copyright_url" => "http://www.electricsheepfencing.com",
	"product_copyright_years" => "2004 - ".date("Y"),
	"product_website" => "www.pfsense.org",
	"product_website_footer" => "https://www.pfsense.org/?gui22",
	"product_email" => "coreteam@pfsense.org",
	"hideplatform" => false,
	"hidedownloadbackup" => false,
	"hidebackupbeforeupgrade" => false,
	"disablethemeselection" => false,
	"disablehelpmenu" => false,
	"disablehelpicon" => false,
	"disablecrashreporter" => false,
	"crashreporterurl" => "https://crashreporter.pfsense.org/crash_reporter.php",
	"debug" => false,
	"latest_config" => "11.8",
	"nopkg_platforms" => array("cdrom"),
	"minimum_ram_warning" => "101",
	"minimum_ram_warning_text" => "128 MB",
	"wan_interface_name" => "wan",
	"nopccard_platforms" => array("wrap", "net48xx"),
	"xmlrpcbaseurl" => "https://packages.pfsense.org",
	"captiveportal_path" => "/usr/local/captiveportal",
	"captiveportal_element_path" => "/var/db/cpelements",
	"captiveportal_element_sizelimit" => 1048576,
	"xmlrpcpath" => "/xmlrpc.php",
	"embeddedbootupslice" => "/dev/ad0a",
	"services_dhcp_server_enable" => true,
	"wireless_regex" => "/^(ndis|wi|ath|an|ral|ural|iwi|wlan|rum|run|bwn|zyd|mwl|bwi|ipw|iwn|malo|uath|upgt|urtw|wpi)/",
	"help_base_url" => "/help.php"
);

/* IP TOS flags */
$iptos = array("lowdelay", "throughput", "reliability");

/* TCP flags */
$tcpflags = array("syn", "ack", "fin", "rst", "psh", "urg", "ece", "cwr");

if (file_exists("/etc/platform")) {
	$arch = php_uname("m");
	$current_version = trim(file_get_contents("{$g['etc_path']}/version"));

	if (strstr($current_version, "-RELEASE")) {
		/* This is only necessary for RELEASE */
		$arch = ($arch == "i386") ? "" : '/' . $arch;
		/* Full installs and NanoBSD use the same update directory and manifest in 2.x */
		$g['update_url']="https://updates.pfsense.org/_updaters{$arch}";
		$g['update_manifest']="https://updates.pfsense.org/manifest";
	} else {
		/* Full installs and NanoBSD use the same update directory and manifest in 2.x */
		$g['update_url']="https://snapshots.pfsense.org/FreeBSD_releng/10.1/{$arch}/pfSense_HEAD/.updaters/";
		$g['update_manifest']="https://updates.pfSense.org/manifest";
	}

	$g['platform'] = trim(file_get_contents("/etc/platform"));
	if ($g['platform'] == "nanobsd") {
		$g['firmware_update_text']="pfSense-*.img.gz";
		$g['hidedownloadbackup'] = true;
		$g['hidebackupbeforeupgrade'] = true;

	} else {
		$g['firmware_update_text']="pfSense-*.tgz";
	}
}

/* Default sysctls */
$sysctls = array("net.inet.ip.portrange.first" => "1024",
	"net.inet.tcp.blackhole" => "2",
	"net.inet.udp.blackhole" => "1",
	"net.inet.ip.random_id" => "1",
	"net.inet.tcp.drop_synfin" => "1",
	"net.inet.ip.redirect" => "1",
	"net.inet6.ip6.redirect" => "1",
	"net.inet6.ip6.use_tempaddr" => "0",
	"net.inet6.ip6.prefer_tempaddr" => "0",
	"net.inet.tcp.syncookies" => "1",
	"net.inet.tcp.recvspace" => "65228",
	"net.inet.tcp.sendspace" => "65228",
	"net.inet.ip.fastforwarding" => "0",
	"net.inet.tcp.delayed_ack" => "0",
	"net.inet.udp.maxdgram" => "57344",
	"net.link.bridge.pfil_onlyip" => "0",
	"net.link.bridge.pfil_member" => "1",
	"net.link.bridge.pfil_bridge" => "0",
	"net.link.tap.user_open" => "1",
	"kern.randompid" => "347",
	"net.inet.ip.intr_queue_maxlen" => "1000",
	"hw.syscons.kbd_reboot" => "0",
	"net.inet.tcp.log_debug" => "0",
	"net.inet.tcp.tso" => "1",
	"net.inet.icmp.icmplim" => "0",
	"vfs.read_max" => "32",
	"kern.ipc.maxsockbuf" => "4262144",
	"debug.pfftpproxy" => "0",
	"net.inet.ip.process_options" => 0,
	"kern.random.sys.harvest.interrupt" => 0,
	"kern.random.sys.harvest.point_to_point" => 0,
	"kern.random.sys.harvest.ethernet" => 0,
	"net.route.netisr_maxqlen" => 1024,
	"net.inet.udp.checksum" => 1,
	"net.bpf.zerocopy_enable" => 1,
	"net.inet.icmp.reply_from_interface" => 1,
	"vfs.forcesync" => "1",
	"net.inet6.ip6.rfc6204w3" => 1,
	"net.enc.out.ipsec_bpf_mask" => "0x0001",
	"net.enc.out.ipsec_filter_mask" => "0x0001",
	"net.enc.in.ipsec_bpf_mask" => "0x0002",
	"net.enc.in.ipsec_filter_mask" => "0x0002",
	"net.key.preferred_oldsa" => "0",
	"net.inet.carp.senderr_demotion_factor" => 0, /* Do not demote CARP for interface send errors */
	"net.pfsync.carp_demotion_factor" => 0 /* Do not demote CARP for pfsync errors */
);

/* Include override values for the above if needed. If the file doesn't exist, don't try to load it. */
if (file_exists("/etc/inc/globals_override.inc")) {
	@include("globals_override.inc");
}

function platform_booting($on_console = false) {
	global $g;

	if ($g['booting'] || file_exists("{$g['varrun_path']}/booting")) {
		if ($on_console == false || php_sapi_name() != 'fpm-fcgi') {
			return true;
		}
	}

	return false;
}

if (file_exists("{$g['cf_conf_path']}/enableserial_force")) {
	$g['enableserial_force'] = true;
}

$config_parsed = false;

?>
