#!/usr/bin/env node

import { spawn } from 'child_process';
import fs from 'fs';
import path from 'path';

// Manual .env loader for child process inheritance
function loadEnv() {
  try {
    const envPath = path.resolve(process.cwd(), '.env');
    if (fs.existsSync(envPath)) {
      const content = fs.readFileSync(envPath, 'utf-8');
      content.split(/\r?\n/).forEach(line => {
        // Match KEY=Value, ignoring comments
        const match = line.match(/^\s*([\w.\-]+)\s*=\s*(.*)?\s*$/);
        if (match) {
          const key = match[1];
          let value = match[2] || '';
          // Remove wrapping quotes if present
          if (value.startsWith('"') && value.endsWith('"')) {
            value = value.slice(1, -1);
          } else if (value.startsWith("'") && value.endsWith("'")) {
            value = value.slice(1, -1);
          }
          process.env[key] = value;
        }
      });
      console.log('✅ Loaded .env variables into process.env');
    }
  } catch (err) {
    console.error('⚠️ Error loading .env:', err);
  }
}

loadEnv();

async function runCommand(command, args = []) {
  return new Promise((resolve, reject) => {
    const child = spawn(command, args, {
      stdio: 'inherit',
      shell: process.platform === 'win32'
    });

    child.on('close', (code) => {
      if (code === 0) {
        resolve();
      } else {
        reject(new Error(`Command failed with code ${code}`));
      }
    });

    child.on('error', (error) => {
      reject(error);
    });
  });
}

async function main() {
  try {
    console.log('🚀 Starting Tauri build process...');

    // Check Linux dependencies first
    console.log('🔍 Checking Linux dependencies...');
    await runCommand('node', ['scripts/check-linux-deps.js']);

    // Run Tauri build
    console.log('🔨 Running Tauri build...');
    await runCommand('npx', ['tauri', 'build']);

    console.log('✅ Build completed successfully!');

  } catch (error) {
    console.error('❌ Build failed:', error.message);
    process.exit(1);
  }
}

main();