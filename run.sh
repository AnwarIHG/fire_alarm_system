#!/bin/env bash

set -ex

arduino-cli compile
arduino-cli upload
