#! /bin/sh
#
# Set Linux system parameters for running programs.
#
# See https://github.com/JuliaCI/BenchmarkTools.jl/blob/master/doc/linuxtips.md
#
prog=$(basename "$0")

die() {
    echo >&2 "$*"
    exit 1
}

print_usage() {
    echo "Usage: [sudo] $prog [-h|--help] [--] [COMMAND]"
}

while test $# -ge 1; do
    case "$1" in
        -h | --help)
            print_usage
            echo "Query or set Linux settings for running programs."
            echo "Commands/options are:"
            echo "    show                Show current settings (default command)."
            echo "    restore             Restore system settings."
            echo "    perf, performance   Set performance settings."
            echo "    stable              Apply settings for reduced jittering."
            echo "    -h, --help          Print this help."
            exit 0
            ;;
        --)
            shift
            break
            ;;
        -*)
            die "Unknown option \"$1\""
            ;;
        *)
            break
            ;;
    esac
done

if test $# -eq 0; then
    command="show"
elif test $# -eq 1; then
    command=$1
else
    die "Too many arguments"
fi

# These were measured once on Linux Mint 20 Ulyana.
orig_vm_swappiness=60
orig_kernel_randomize_va_space=2
orig_kernel_perf_cpu_time_max_percent=25
orig_scaling_governor=ondemand
orig_cpufreq_boost=1

# Restore original parameters.
restore_settings() {
    sysctl vm.swappiness=$orig_vm_swappiness
    sysctl kernel.randomize_va_space=$orig_kernel_randomize_va_space
    sysctl kernel.perf_cpu_time_max_percent=$orig_kernel_perf_cpu_time_max_percent
    echo $orig_scaling_governor \
        | tee >/dev/null /sys/devices/system/cpu/cpu[0-9]*/cpufreq/scaling_governor
    echo $orig_cpufreq_boost >/sys/devices/system/cpu/cpufreq/boost
}

# See https://github.com/JuliaCI/BenchmarkTools.jl/blob/master/doc/linuxtips.md
# for the following settings.  I have noticed that keeping cpufreq_boost=1 yields
# better performances (this is the only difference compared to "stable" settings).
perf_vm_swappiness=10
perf_kernel_randomize_va_space=0
perf_kernel_perf_cpu_time_max_percent=1
perf_scaling_governor=performance
perf_cpufreq_boost=1

performance_settings() {
    sysctl vm.swappiness=$perf_vm_swappiness
    sysctl kernel.randomize_va_space=$perf_kernel_randomize_va_space
    sysctl kernel.perf_cpu_time_max_percent=$perf_kernel_perf_cpu_time_max_percent
    echo $perf_scaling_governor \
        | tee >/dev/null /sys/devices/system/cpu/cpu[0-9]*/cpufreq/scaling_governor
    echo $perf_cpufreq_boost >/sys/devices/system/cpu/cpufreq/boost
}

# The following is to limit the jittering.
stable_vm_swappiness=10
stable_kernel_randomize_va_space=0
stable_kernel_perf_cpu_time_max_percent=1
stable_scaling_governor=performance
stable_cpufreq_boost=0

stable_settings() {
    sysctl vm.swappiness=$stable_vm_swappiness
    sysctl kernel.randomize_va_space=$stable_kernel_randomize_va_space
    sysctl kernel.perf_cpu_time_max_percent=$stable_kernel_perf_cpu_time_max_percent
    echo $stable_scaling_governor \
        | tee >/dev/null /sys/devices/system/cpu/cpu[0-9]*/cpufreq/scaling_governor
    echo $stable_cpufreq_boost >/sys/devices/system/cpu/cpufreq/boost
}

# Show current parameters.
show_settings() {
    local dir val glb flg i n
    sysctl vm.swappiness
    sysctl kernel.randomize_va_space
    sysctl kernel.perf_cpu_time_max_percent
    printf "cpufreq boost = "
    cat /sys/devices/system/cpu/cpufreq/boost
    glb=""
    flg="true"
    n=0
    for dir in /sys/devices/system/cpu/cpu[0-9]*; do
        val=$(cat "$dir/cpufreq/scaling_governor")
        if test $n -eq 0; then
            glb=$val
        elif test "$val" != "$glb"; then
            flg="false"
        fi
        n=$(expr $n + 1)
    done
    if test "$flg" = "true"; then    
        printf "cpufreq scaling_governor = %s (for all CPUs)\n" "$glb"
    else
        i=0
        while test $i -lt $n; do
            val=$(cat "/sys/devices/system/cpu/cpu$i/cpufreq/scaling_governor")
            printf "cpufreq scaling_governor %2d = %s\n" $i "$val"
            i=$(expr $i + 1)
        done
    fi
}

case "$command" in
    show )
        show_settings
        ;;
    restore )
        restore_settings
        ;;
    stable )
        stable_settings
        ;;
    perf | performance )
        performance_settings
        ;;
    *)
        die "Unknown command \"$command\""
        ;;
esac
exit 0
